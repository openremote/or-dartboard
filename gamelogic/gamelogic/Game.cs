using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DartboardGameServer
{
    class Game
    {
        private int NumberOfPlayers;
        private int GameMode;
        public List<Player> PlayerList;


        // Description:
        //      Constructor for the Game class.
        // Restrains:
        //      NumberOfPlayers can't be below 0.
        //      GameMode can't be below 0.
        public Game(int numberOfPlayers, int gameMode)
        {
            if (numberOfPlayers <= 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be 0 or lower");
            }
            if (gameMode < 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be lower than 0");
            }

            NumberOfPlayers = numberOfPlayers;
            GameMode = gameMode;
            PlayerList = new List<Player>();
        }

        // Description:
        //      Use the incoming data from the dart.
        // Returns:
        //      New player score.
        // Restrains:
        //      Player can't be below 0.
        //      DartValue can't be below 0.
        public virtual int ProcessDart(int currentPlayer, int dartValue)
        {
            if (currentPlayer < 0 || dartValue < 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be lower than 0");
            }
            // Value is less or equal to the score.
            else
            {
                PlayerList[currentPlayer].AddScore(dartValue);
                return PlayerList[currentPlayer].Score;
            }
        }

        // Description:
        //      Get the score of the player.
        // Returns:
        //      The score of the player.
        // Restrains:
        //      currentPlayer can't be 0 or lower.
        public int GetPlayerScore(int currentPlayer)
        {
            if (currentPlayer < 0)
            {
                throw new IndexOutOfRangeException("Parameter cannot be lower than 0");
            }

            Player player = PlayerList[currentPlayer];
            return player.Score;
        }
    }
}