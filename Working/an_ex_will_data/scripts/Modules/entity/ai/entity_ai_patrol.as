namespace Entity
{
    namespace AI
    {
        class Patrol
        {
            Patrol(Character@ character, ShouldMove@ shouldMove, array<Atmos::Spatial::Grid::Point> waypoints)
            {
                if (waypoints.length() == 0)
                    throw("Patrol requires waypoints.");
            
                @this.character = @character;
                @this.shouldMove = @shouldMove;
                this.route = waypoints;
                this.currentPath = Path(FindPathDirections(waypoints[0]), @character);
            }
            
            void Execute()
            {
                if (character.IsMoving() || !shouldMove(character))
                    return;
                
                if (!currentPath.IsDone())
                    currentPath.Execute();
                else
                    StartNextWaypoint();
            }
            
            private Character@ character;
            private ShouldMove@ shouldMove;
            
            private Path currentPath;
            
            private uint waypointIndex = 0;
            private array<Atmos::Spatial::Grid::Point> route;
            
            private void StartNextWaypoint()
            {
                ++waypointIndex;
                if (waypointIndex == route.length())
                    waypointIndex = 0;
                
                const auto possiblePathDirections = FindPathDirections(route[waypointIndex]);
                if (possiblePathDirections.length() == 0)
                    StartNextWaypoint();
                else
                    currentPath = Path(possiblePathDirections, @character);
                    
                Arca::Reliquary::Do(Atmos::Logging::Log(Atmos::ToString(waypointIndex)));
            }
            
            private array<CharacterDirection> FindPathDirections(Atmos::Spatial::Grid::Point to) const
            {
                const auto entity = Atmos::Entity::Entity(character.ID());
                const auto pathPoints = Arca::Reliquary::Do(Atmos::Entity::FindPath(entity, to));
                return ToDirections(pathPoints);
            }
            
            private array<CharacterDirection> ToDirections(array<Atmos::Spatial::Grid::Point> points) const
            {
                if (points.length() == 0)
                    return {};
                
                array<CharacterDirection> directions;
                for (uint i = 1; i < points.length(); ++i)
                {
                    auto previousPoint = points[i - 1];
                    auto currentPoint = points[i];
                    
                    directions.insertLast(ToDirection(previousPoint, currentPoint));
                }
                
                return directions;
            }
            
            private CharacterDirection ToDirection(Atmos::Spatial::Grid::Point first, Atmos::Spatial::Grid::Point second) const
            {
                if (first.x > second.x)
                    return CharacterDirection::Left;
                else if (first.y > second.y)
                    return CharacterDirection::Up;
                else if (first.x < second.x)
                    return CharacterDirection::Right;
                else if (first.y < second.y)
                    return CharacterDirection::Down;
                else
                {
                    throw("Cannot determine direction.");
                    return CharacterDirection::Left;
                }
            }
        }
        
        array<Atmos::Spatial::Grid::Point> CreateReversedPatrolWaypoints(array<Atmos::Spatial::Grid::Point> waypoints)
        {
            if (waypoints.length() == 0 || waypoints.length() == 1)
                return waypoints;
        
            array<Atmos::Spatial::Grid::Point> reversed = waypoints;
            reversed.reverse();
            reversed.insertLast(reversed[0]);
            reversed.removeAt(0);
            
            auto returnValue = waypoints;
            for(uint i = 0; i < reversed.length(); ++i)
                returnValue.insertLast(reversed[i]);
            return returnValue;
        }
    }
}