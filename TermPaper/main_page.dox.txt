/**
*\mainpage
*<h1 id="thisisabriefdocumentationforjust2dplatformer">This is a brief documentation for JUST2D Platformer</h1>
*
*<h3 id="howtorunagame">How to run a game:</h3>
*
*<p><em>Attention! This is GoofleTranslated page</em></p>
*
*<p>The application is supplied as a .7z archive.
*This software product does not require installation. It can be launched from any media (USB Flash, CD, DVD, external hard disk), and from the directory of operating system directories.
*Unzip the contents of the archive into a convenient place for you. Do not delete, move, or modify any other files in the unpacked directory. This can lead to a complete or partial loss of the program.
*Go to the root directory of the unpacked application and run the file. Have a good game!</p>
*
*<p>Control keys:</p>
*
*<ul>
*<li>Right - move character to the right</li>
*
*<li>Left - move character to the left</li>
*
*<li>Up - Jump</li>
*
*<li>C - switch to another character</li>
*
*<li>P - pick up the box (strong character)</li>
*
*<li>click the mouse - throw the box in the specified direction</li>
*
*<li>I - activate the lever</li>
*</ul>
*
*<h3 id="howtocreatealevelforleveldesigneronly">How to create a level (for level designer only)</h3>
*
*<p><em>Attention! This is GoofleTranslated page</em></p>
*
*<p>Information about the level is stored in a file of the .tmx format, it is recommended to use the freely distributed TiledMap Editor to generate files of this format. Here is the instruction to create a level using this program.
*When creating a level, specify the format of the CSV layer.
*If the game level needs a background, then set the background layers according to the TiledMap Editor.
*Note that all objects on the level must have a rectangular shape.
*Form the following groups of objects:</p>
*
*<ul>
*<li>Dangers</li>
*
*<li>Sensors</li>
*
*<li>Kinematic</li>
*
*<li>Static</li>
*
*<li>Dynamic</li>
*</ul>
*
*<p>In the group of Static objects, add "land" objects; for them, you do not need to specify anything additional, or objects of "mortal danger" type, for them type "danger" in the object type.</p>
*
*<p>In the group of Dynamic objects add two objects in the type of which specify "player", as the name of one object is selected "strong<em>player", for another - "dexterous</em>player". It will be a strong and clever character. As the properties of the object they need to set the "health" field - the health level in figures and "image" (it is recommended to specify the standard sizes of objects 32x48 and 32x32 pixels for strong and deft, respectively, and a standard set of images).</p>
*
*<pre><code>In addition, the Dynamic group can be added:
*
*    1. An object of the partition type (specify the partition type), setting the following characteristics for it: "ancor" - the location of the partitioning to the level relative to its center (normal values, eg -1 0), "image", "max_angle" "Min_angle" is the minimum angle of rotation.
*    2. Bridge type object (specify bridge type), properties are set in the same way as partition properties, with the addition of "init_state" - the initial state of the bridge "up", "down" or "stop" is specified, which determines its behavior at level start, "speed" - indicates the speed of the bridge.
*    3. Object type box (specify the type is not necessary) in the properties is indicated "image" and "density" - the gravity factor of the box (determines the possibility and speed of its movement by characters)
*</code></pre>
*
*<p>In the Kinematic object group, you can add:</p>
*
*<pre><code>    1. A broken line is a trajectory (you do not need to specify a type), the properties indicate a logical value "is_rounded" a closed path or not
*    2. Platform (platform type). The following properties are specified: "image", "is_auto" is a logical value, determines whether it is possible to control the platform with the lever, "speed" is the platform speed, "steps" is the number of nodes of the path that it passes to the stop (for is_auto = 0) , "Trajectory" indicates the name of the trajectory, according to which it must follow
*    3. Bonus (type of bonus). The following properties are indicated: "image", "type" - bonus type ("speed", "jump", "health" - health), "modificator" - force of impact in times for jump and speed and units For health, "time" - the validity period of bonuses, except health
*</code></pre>
*
*<p>Two objects with the type "final" are added to the group of Sensors objects, they are indicated by the properties "image" and "player" -type of the player that activates the exit point "strong" or "dexterous"</p>
*
*<pre><code>You can also add:
*
*    1. Sensor (sensor type). The following properties are specified: "is_visible" is a Boolean value, indicates a visible or invisible object, "is_keeping" is a Boolean value, indicates whether to permanently be near the object to activate it, "image" - is specified only for visible
*    2. Timer (type timer). The following properties are specified: "is_rounded" - a logical value, determines whether to start counting first after the completion of the previous iteration, "time_stages" - the number of switching in one iteration
*    3. The lever (type lever). The "image" property
*
*For all sensor objects, the following properties are also specified: "observables" - a list of names of bridges and platforms that are controlled by this sensor, "repeat_allowed" - a logical value, whether it is possible to reactivate if the previous one has not yet completed, "stages" - only for Bridges (optional), the order of the commands (indicated above as bridge states), which are executed by the bridge every time the sensor is activated, are indicated via a space.
*</code></pre>
*
*<p>Danger objects are added to the group of Dangers objects with the following characteristics: "image", "damage" - the level of damage inflicted to the player during the contact, "down<em>side" "up</em>side" "left<em>side" "right</em>side" - logical values, determine which side of the object Is dangerous for the player (can be combined), "is<em>movable" - a logical value, whether the dangerous object moves or not, "stick</em>platform" - specifies the name of the platform that will take the properties of the dangerous object if it moves.</p>
*
*<p>Adding characters and exit points for them at the level is a prerequisite, everything else is added at the discretion of the developer of the level, but you must correctly specify all properties of the added objects, otherwise the level will not be started or will not work correctly.</p>
*/