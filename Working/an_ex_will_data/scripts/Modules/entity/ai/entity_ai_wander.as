namespace Entity
{
    namespace AI
    {
        namespace Detail
        {
            funcdef void WanderMovement();
        }
        
        class Wander
        {
            Wander(Character@ character, ShouldMove@ shouldMove, Atmos::Spatial::Grid::AxisAlignedBox movementRegion)
            {
                @this.character = @character;
                @this.shouldMove = @shouldMove;
                this.movementRegion = movementRegion;
            }
            
            void Execute()
            {
                if (character.IsMoving() || !shouldMove(character))
                    return;
            
                array<Entity::AI::Detail::WanderMovement@> possibleMovements;
            
                if (CanMoveLeft())
                    possibleMovements.insertLast(Entity::AI::Detail::WanderMovement(this.MoveLeft));
                if (CanMoveUp())
                    possibleMovements.insertLast(Entity::AI::Detail::WanderMovement(this.MoveUp));
                if (CanMoveRight())
                    possibleMovements.insertLast(Entity::AI::Detail::WanderMovement(this.MoveRight));
                if (CanMoveDown())
                    possibleMovements.insertLast(Entity::AI::Detail::WanderMovement(this.MoveDown));
                if (CanMoveLeft())
                
                if (possibleMovements.length() == 0)
                    return;
                
                const auto selectedMovement =
                    Arca::Reliquary::Do(Atmos::Random::GenerateInt(Atmos::IntRange(0, possibleMovements.length() - 1)));
                
                possibleMovements[selectedMovement]();
            }
            
            private Character@ character;
            private ShouldMove@ shouldMove;
            
            private Atmos::Spatial::Grid::AxisAlignedBox movementRegion;
            
            private void MoveLeft()
            {
                character.Move(CharacterDirection::Left);
            }
            
            private void MoveUp()
            {
                character.Move(CharacterDirection::Up);
            }
            
            private void MoveRight()
            {
                character.Move(CharacterDirection::Right);
            }
            
            private void MoveDown()
            {
                character.Move(CharacterDirection::Down);
            }
            
            private bool CanMoveLeft() const
            {
                const auto currentPosition = character.Position();
                const auto nextPosition = Atmos::Spatial::Grid::Point(currentPosition.x - 1, currentPosition.y);
                return Atmos::Spatial::Grid::Contains(movementRegion, nextPosition) && character.CanMove(CharacterDirection::Left);
            }
            
            private bool CanMoveUp() const
            {
                const auto currentPosition = character.Position();
                const auto nextPosition = Atmos::Spatial::Grid::Point(currentPosition.x, currentPosition.y - 1);
                return Atmos::Spatial::Grid::Contains(movementRegion, nextPosition) && character.CanMove(CharacterDirection::Up);
            }
            
            private bool CanMoveRight() const
            {
                const auto currentPosition = character.Position();
                const auto nextPosition = Atmos::Spatial::Grid::Point(currentPosition.x + 1, currentPosition.y);
                return Atmos::Spatial::Grid::Contains(movementRegion, nextPosition) && character.CanMove(CharacterDirection::Right);
            }
            
            private bool CanMoveDown() const
            {
                const auto currentPosition = character.Position();
                const auto nextPosition = Atmos::Spatial::Grid::Point(currentPosition.x, currentPosition.y + 1);
                return Atmos::Spatial::Grid::Contains(movementRegion, nextPosition) && character.CanMove(CharacterDirection::Down);
            }
        }
    }
}