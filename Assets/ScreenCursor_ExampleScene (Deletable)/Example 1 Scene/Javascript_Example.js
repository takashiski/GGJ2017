private var RandomVector2 : Vector2;
private var CursorVisibility : boolean = true;
private var CursorVisibility1 : boolean = true;
var TestCoords : Vector2;
private var X : String;
private var Y : String;



	function Start () {
		HardwareCursor.SetSavesLength(2); // Set the maximun save files ( it can be called at any time but its recommended to be done at start or awake!! )
	}
	function Update () {
		
		if (!CursorVisibility || !CursorVisibility1) {	// Lines 15,16,17,18
			Cursor.visible = false;		}				// say that when the "CursorVisibility" variable is true/false also hide/show the cursor
		if (CursorVisibility && CursorVisibility1) {	// with Unity's way of doing it.
			Cursor.visible = true;		}
		
		if (Input.GetKey(KeyCode.Q)) {				// Lines 20,21,22,23,24,25,26
			Cursor.lockState = CursorLockMode.Locked;// say that when we press and hold the "Q" buttonm the Cursor will be locked and stay invisible
			CursorVisibility1 = false;				// in the center of the screen with Unity's way of doing it.
		} else {
			Cursor.lockState = CursorLockMode.None;
			CursorVisibility1 = true;
		}
		
		
		if (Input.GetKeyDown(KeyCode.Mouse1)) { // Lines 29-32
			CursorVisibility = false;			// say that when we pres down our Right mouse click, the cursor will turn invisible
			HardwareCursor.SavePosition();		// and its position will be stored in a variable
		}
		if (Input.GetKeyUp(KeyCode.Mouse1)) {	// Lines 33-36
			HardwareCursor.LoadPosition();				// say that when we release our Right mouse click, the curor's position will be restored
			CursorVisibility = true;			// and then it will turn visible again ( note: we do this in that frame order so no visible mouse teleporting happens )
		}
		
		if (Input.GetKeyDown(KeyCode.B)) {			// Lines 38,39
			HardwareCursor.SetPosition(TestCoords.x,TestCoords.y); }
		// above line say that when we press the "B" buttonm the Cursor will go to TestCoords that were set from the inspector
		if (Input.GetKeyDown(KeyCode.C)) {			// Lines 41,42 do exacly as above but with random coordinates whenever we press "C"
			HardwareCursor.SetLocalPosition(Random.Range(0,Screen.width),Random.Range(0,Screen.height)); }
		
		if (Input.GetKeyDown("1")) {			// Lines 44,45 Save first position when we press "1"
			HardwareCursor.SavePosition(1); }
		
		if (Input.GetKeyDown("2")) {			// Lines 47,48 Save second position when we press "2"
			HardwareCursor.SavePosition(2); }
		
		if (Input.GetKeyDown("3")) {			// Lines 50,51 Load first position when we press "3"
			HardwareCursor.LoadPosition(1); }
		
		if (Input.GetKeyDown("4")) {			// Lines 53,54 Load second position when we press "4"
			HardwareCursor.LoadPosition(2); }
		
		if (float.TryParse(X,TestCoords.x)) {}
		if (float.TryParse(Y,TestCoords.y)) {}
		// WARNING !
		// Read the InstalationGuide.txt and the ReadMe.txt
				
		if (Input.GetKeyDown(KeyCode.H) || Input.GetKeyDown(KeyCode.U)) {
			RandomVector2 = Vector2(Random.Range(0,Screen.width),Random.Range(0,Screen.height));
		}
		if (Input.GetKey(KeyCode.H)) {  //Press H to simulate an automatic random cursor move
			HardwareCursor.SimulateAutoMove(RandomVector2,0.2f);
		}
		if (Input.GetKey(KeyCode.U)) {  //Press U to simulate a manual random cursor move
			HardwareCursor.SimulateLocalMove(RandomVector2,0.2f);
		}
		if (Input.GetKeyDown(KeyCode.P)) {  //Press P to store cursor position as a Vector2
			TestCoords = HardwareCursor.GetPosition(); }
		
		if (Input.GetKeyDown(KeyCode.Z)) {
			HardwareCursor.LeftClick(); //Translate "Z" keydown to a full left mouse click
		}
		if (Input.GetKeyDown(KeyCode.X)) {
			HardwareCursor.RightClick(); //Translate "X" keydown to a full right mouse click
		}
		
		HardwareCursor.LeftClickEquals(KeyCode.Space); //Defines the "Space" key as a left mouse
	}
	
	function OnGUI () {
		GUI.Label(Rect(5,0,80,20),"X :");
		X = GUI.TextArea(Rect(20,0,80,20),""+TestCoords.x);
		GUI.Label(Rect(100,0,80,20),"Y :");
		Y = GUI.TextArea(Rect(115,0,80,20),""+TestCoords.y);
		GUI.Label(Rect(5,30,800,40),"Only numbers above or else values will return Zero \n(Also above system is working on 'Global' mode , if you want to use Unity's coordinates system use the same functions with 'Local')");
		
		if ( GUI.Button(Rect(200,0,100,20),"Set Cursor")) {
			HardwareCursor.SetPosition(TestCoords.x,TestCoords.y); 
		}
		GUI.Label(Rect(5,65,500,20),"Current Unity/Local Cursor Position: "+HardwareCursor.GetLocalPosition().x+" , "+HardwareCursor.GetLocalPosition().y);
		GUI.Label(Rect(5,80,500,20),"Current Global Cursor Position: "+HardwareCursor.GetPosition().x+" , "+HardwareCursor.GetPosition().y);
	}