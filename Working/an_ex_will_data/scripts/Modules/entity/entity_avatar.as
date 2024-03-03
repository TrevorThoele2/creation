namespace Entity
{
    class Avatar : Character
    {
        Avatar(
            Arca::RelicID entityID,
            Arca::RelicID imageID,
            CharacterAnimation leftAnimation,
            CharacterAnimation upAnimation,
            CharacterAnimation rightAnimation,
            CharacterAnimation downAnimation,
            Atmos::Time::Nanoseconds duration)
        {
            super(entityID, imageID, leftAnimation, upAnimation, rightAnimation, downAnimation, duration);
        }
        
        bool Execute()
        {
            if (moveLeftAction.IsActive())
                Move(CharacterDirection::Left);
            else if (moveUpAction.IsActive())
                Move(CharacterDirection::Up);
            else if (moveRightAction.IsActive())
                Move(CharacterDirection::Right);
            else if (moveDownAction.IsActive())
                Move(CharacterDirection::Down);
        
            return Character::Execute();
        }
        
        private ActionStabilizer moveLeftAction(Assets::Action::moveLeft());
        private ActionStabilizer moveUpAction(Assets::Action::moveUp());
        private ActionStabilizer moveRightAction(Assets::Action::moveRight());
        private ActionStabilizer moveDownAction(Assets::Action::moveDown());
    }
}