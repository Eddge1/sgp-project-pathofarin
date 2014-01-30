using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace SGP_PoA_LevelEditor
{
    struct myUnits
    {
        int hp;
        int ap;
        int attack;
        string name;
        string ai;

    };

    struct myNPC
    {
        string name;
        bool moves;
        bool isHostile;
        List<myUnits> units;
        List<Point> waypoints;

        public bool IsHostile
        {
            get { return isHostile; }
            set { isHostile = value; }
        }

        public bool Moves
        {
            get { return moves; }
            set { moves = value; }
        }

        public List<myUnits> Units
        {
            get { return units; }
            set { units = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public List<Point> Waypoints
        {
            get { return waypoints; }
            set { waypoints = value; }
        }

        public override string ToString()
        {
            return Name + ".xml";
        }


    }
}
