namespace Entity
{
    namespace AI
    {
        class Path
        {
            Path()
            {}
        
            Path(array<CharacterDirection> directions, Character@ character)
            {
                this.directions = directions;
                @this.character = @character;
            }
            
            void Execute()
            {
                if (IsDone() || character.IsMoving())
                    return;
                
                character.Move(directions[index]);
                ++index;
            }
            
            bool IsDone() const
            {
                return index == directions.length();
            }
        
            private array<CharacterDirection> directions;
            private uint index = 0;
            
            private Character@ character;
        }
    }
}