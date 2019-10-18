DIR="ProcessTracker"

if ! [ -d "$DIR" ]; then
  mkdir $DIR;
fi

cp LICENSE $DIR;

cp Tracker/target/release/tracker $DIR;

if ! [ -f "$DIR/tracker.db"  ] ; then
  cp Tracker/src/tracker.db $DIR
fi

cp TrackerGUI/gui $DIR;

cp -r TrackerGUI/images $DIR;

cp run_tracker_shit.sh $DIR;