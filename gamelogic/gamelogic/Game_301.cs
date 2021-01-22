using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DartboardGameServer
{
    class Game_301 : Game
    {
        private int InitialScore = 301;
        

        public Game_301(int numberOfPlayers, int gameMode) : base(numberOfPlayers, gameMode)
        {
            if (numberOfPlayers < 0 || gameMode < 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be lower than 0");
            }

            for (int i = 0; i < numberOfPlayers; i++)
            {
                Player player = new Player(i.ToString(), InitialScore);
                PlayerList.Add(player);
            }
        }

        // Description:
        //      Use the incoming data from the dart.
        // Returns:
        //      New player score.
        // Restrains:
        //      Player can't be below 0.
        //      DartValue can't be below 0.
        public override int ProcessDart(int currentPlayer, int dartValue)
        {
            if (currentPlayer < 0 || dartValue < 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be lower than 0");
            }

            // Value is too high and turn will be forfeit.
            if (PlayerList[currentPlayer].Score < dartValue)
            {
                return -1;
            }
            // Value is equal or lower than the player's score.
            else
            {
                PlayerList[currentPlayer].SubtractScore(dartValue);
                return PlayerList[currentPlayer].Score;
            }
        }
    }
}
