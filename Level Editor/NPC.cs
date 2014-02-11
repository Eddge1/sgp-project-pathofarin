using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SGP_PoA_LevelEditor
{
    struct myUnits
    {
        int hp;
        int ap;
        int attack;
        int exp;
        int speed;
        int level;
        string name;
        string ai;
        string animation;
        List<string> szItems;
        List<decimal> fChances;

        public int Speed
        {
            get { return speed; }
            set { speed = value; }
        }

        public int Level
        {
            get { return level; }
            set { level = value; }
        }

        public string Animation
        {
            get { return animation; }
            set { animation = value; }
        }
        public List<decimal> DropChance
        {
            get { return fChances; }
            set { fChances = value; }
        }

        public List<string> SzItems
        {
            get { return szItems; }
            set { szItems = value; }
        }

        public int Exp
        {
            get { return exp; }
            set { exp = value; }
        }

        public int Hp
        {
            get { return hp; }
            set { hp = value; }
        }

        public int Ap
        {
            get { return ap; }
            set { ap = value; }
        }

        public int Attack
        {
            get { return attack; }
            set { attack = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Ai
        {
            get { return ai; }
            set { ai = value; }
        }

        public override string ToString()
        {
            return Name + " the Unit";
        }
    };

    struct myNPC
    {
        string name;
        bool moves;
        bool isHostile;
        string animation;
        List<myUnits> units;
        List<Point> waypoints;
        List<myConvo> lConvos;

        internal List<myConvo> MyConvos
        {
            get { return lConvos; }
            set { lConvos = value; }
        }

        public string Animation
        {
            get { return animation; }
            set { animation = value; }
        }

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
            return Name;
        }
    }

    struct myConvo
    {
        string szConvos;
        string szEvent;

        public string SzEvent
        {
            get { return szEvent; }
            set { szEvent = value; }
        }

        public string SzConvos
        {
            get { return szConvos; }
            set { szConvos = value; }
        }
        public override string ToString()
        {
            return szConvos;
        }
    }
}
