namespace Entity
{
    class Character
    {
        Character(
            Arca::RelicID entityID,
            Arca::RelicID imageID,
            CharacterAnimation leftAnimation,
            CharacterAnimation upAnimation,
            CharacterAnimation rightAnimation,
            CharacterAnimation downAnimation,
            Atmos::Time::Nanoseconds duration)
        {
            this.entityID = entityID;
            this.imageID = imageID;
            
            this.leftAnimation = leftAnimation;
            this.upAnimation = upAnimation;
            this.rightAnimation = rightAnimation;
            this.downAnimation = downAnimation;
            
            this.duration = duration;
            
            Arca::Reliquary::Do(Atmos::Spatial::MoveBoundsTo(imageID, ToImagePosition(Position())));
        }
        
        void Move(CharacterDirection direction)
        {
            switch(direction)
            {
            case CharacterDirection::Left:
                AttemptMove(this.leftAnimation, Modulation::On(this.ChangeImageXPosition), nextLeftPosition, xPositionComponent);
                break;
            case CharacterDirection::Up:
                AttemptMove(this.upAnimation, Modulation::On(this.ChangeImageYPosition), nextUpPosition, yPositionComponent);
                break;
            case CharacterDirection::Right:
                AttemptMove(this.rightAnimation, Modulation::On(this.ChangeImageXPosition), nextRightPosition, xPositionComponent);
                break;
            case CharacterDirection::Down:
                AttemptMove(this.downAnimation, Modulation::On(this.ChangeImageYPosition), nextDownPosition, yPositionComponent);
                break;
            default:
                throw("Unknown CharacterDirection");
                break;
            }
        }
        
        bool CanMove(CharacterDirection direction) const
        {
            switch(direction)
            {
            case CharacterDirection::Left:
                return CanMoveRelative(nextLeftPosition);
            case CharacterDirection::Up:
                return CanMoveRelative(nextUpPosition);
            case CharacterDirection::Right:
                return CanMoveRelative(nextRightPosition);
            case CharacterDirection::Down:
                return CanMoveRelative(nextDownPosition);
            default:
                throw("Unknown CharacterDirection");
            }
            
            return false;
        }
        
        bool IsMoving() const
        {
            return IsRunning();
        }
        
        bool Execute()
        {
            for (uint i = runningModulators.length(); i > 0; --i)
            {
                const auto modulator = runningModulators[i - 1];
                if (modulator.Execute())
                    runningModulators.removeAt(i - 1);
            }
            
            return !IsRunning();
        }
        
        Atmos::Spatial::Grid::Point Position() const
        {
            const auto entity = Atmos::Entity::Entity(entityID);
            return entity.Position();
        }
        
        Arca::RelicID ID() const
        {
            return entityID;
        }
        
        Arca::RelicID ImageID() const
        {
            return imageID;
        }
        
        private Arca::RelicID entityID;
        private Arca::RelicID imageID;
        
        private CharacterAnimation leftAnimation;
        private CharacterAnimation upAnimation;
        private CharacterAnimation rightAnimation;
        private CharacterAnimation downAnimation;
        
        private Atmos::Time::Nanoseconds duration;
        private array<Modulation::Modulator@> runningModulators;
        
        private Entity::Detail::CharacterSelectNextPosition@ nextLeftPosition =
            function(position) { return Atmos::Spatial::Grid::Point(position.x - 1, position.y); };
        private Entity::Detail::CharacterSelectNextPosition@ nextUpPosition =
            function(position) { return Atmos::Spatial::Grid::Point(position.x, position.y - 1); };
        private Entity::Detail::CharacterSelectNextPosition@ nextRightPosition =
            function(position) { return Atmos::Spatial::Grid::Point(position.x + 1, position.y); };
        private Entity::Detail::CharacterSelectNextPosition@ nextDownPosition =
            function(position) { return Atmos::Spatial::Grid::Point(position.x, position.y + 1); };
        
        private Entity::Detail::CharacterSelectPositionValue@ xPositionComponent =
            function(position) { return position.x; };
        private Entity::Detail::CharacterSelectPositionValue@ yPositionComponent =
            function(position) { return position.y; };
        
        private void AttemptMove(
            CharacterAnimation animation,
            Modulation::On@ onMovement,
            Entity::Detail::CharacterSelectNextPosition@ selectNextPosition,
            Entity::Detail::CharacterSelectPositionValue@ selectPositionValue)
        {
            const auto currentPosition = Position();
            const auto nextPosition = selectNextPosition(currentPosition);
            
            if (!IsRunning() && Arca::Reliquary::Do(Atmos::Entity::CanMoveTo(Atmos::Entity::Entity(entityID), nextPosition)))
            {
                Arca::Reliquary::Do(Atmos::Entity::MoveTo(entityID, nextPosition));
                
                const auto currentImagePosition = ToImagePosition(currentPosition);
                const auto nextImagePosition = ToImagePosition(nextPosition);
                const auto movementModulator = Modulation::Modulator(
                {
                    ToMovementNode(
                        selectPositionValue(currentImagePosition),
                        selectPositionValue(nextImagePosition),
                        onMovement)
                });
                
                const auto animationModulator = Modulation::Modulator({ ToAnimationNode(animation, Modulation::On(this.ChangeImageIndex)) });
                
                runningModulators.insertLast(movementModulator);
                runningModulators.insertLast(animationModulator);
            }
        }
        
        private bool CanMoveRelative(Entity::Detail::CharacterSelectNextPosition@ selectNextPosition) const
        {
            const auto currentPosition = Position();
            const auto nextPosition = selectNextPosition(currentPosition);
            return CanMoveTo(nextPosition);
        }
        
        private bool CanMoveTo(Atmos::Spatial::Grid::Point to) const
        {
            if (IsMoving())
                return false;
        
            const auto entity = Atmos::Entity::Entity(entityID);
            return Arca::Reliquary::Do(Atmos::Entity::CanMoveTo(entity, to));
        }
        
        private bool IsRunning() const
        {
            return runningModulators.length() != 0;
        }
        
        private void ChangeImageIndex(double value)
        {
            const auto index = int(Atmos::Floor(value));
            Arca::Reliquary::Do(Atmos::Render::ChangeAssetIndex(imageID, index));
        }
        
        private void ChangeImageXPosition(double value)
        {
            auto position = Atmos::Render::DynamicImage(imageID).Position();
            position.x = value;
            Arca::Reliquary::Do(Atmos::Spatial::MoveBoundsTo(imageID, position));
        }
        
        private void ChangeImageYPosition(double value)
        {
            auto position = Atmos::Render::DynamicImage(imageID).Position();
            position.y = value;
            Arca::Reliquary::Do(Atmos::Spatial::MoveBoundsTo(imageID, position));
        }
        
        private Atmos::Spatial::Point3D ToImagePosition(Atmos::Spatial::Grid::Point position) const
        {
            const auto basePosition = Atmos::Spatial::ToPoint3D(position, 32);
            const auto halfGridCell = Spatial::Grid::cellSize / 2;
            return Atmos::Spatial::Point3D(basePosition.x + halfGridCell, basePosition.y + halfGridCell, basePosition.z);
        }
        
        private Modulation::Node ToMovementNode(double startValue, double endValue, Modulation::On@ on) const
        {
            return Modulation::Node(
                startValue,
                endValue,
                Atmos::Time::ToNanoseconds(Atmos::Time::Milliseconds(0)),
                duration,
                Modulation::Linear,
                on);
        }
        
        private Modulation::Node ToAnimationNode(CharacterAnimation animation, Modulation::On@ on) const
        {
            return Modulation::Node(
                animation.indices.min,
                animation.indices.max,
                Atmos::Time::ToNanoseconds(Atmos::Time::Milliseconds(0)),
                duration,
                animation.interpolation,
                on);
        }
    }

    class CharacterAnimation
    {
        Atmos::IntRange indices;
        Modulation::Interpolation@ interpolation;
        
        CharacterAnimation()
        {}
        
        CharacterAnimation(Atmos::IntRange indices, Modulation::Interpolation@ interpolation)
        {
            this.indices = indices;
            @this.interpolation = @interpolation;
        }
    }

    namespace Detail
    {
        funcdef double CharacterSelectPositionValue(Atmos::Spatial::Point3D);
        funcdef Atmos::Spatial::Grid::Point CharacterSelectNextPosition(Atmos::Spatial::Grid::Point);
    }
}