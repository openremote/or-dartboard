using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DartboardGameServer
{
    class Player
    {
        public string Name;
        public int Score { get; private set; }

        public Player(string name, int score)
        {
            Name = name;
            Score = score;
        }

        // Description
        //      Adds points from the players current score
        public void AddScore(int value)
        {
            if (value < 0)
            {
                value = 0;
            }

            Score += value;
        }

        // Description:
        //      Deduct points from the players current score.
        public void SubtractScore(int value)
        {
            if (value < 0)
            {
                value = 0;
            }

            Score -= value;
            if (Score < 0)
            {
                Score = 0;
            }
        }

        // Description:
        //      Current information about the player.
        // Returns:
        //      Player name and current score.
        public override string ToString()
        {
            return "Player " + Name + ": " + Score;
        }
    }
}
