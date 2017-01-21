using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SerialTest : MonoBehaviour {

    public SerialHandler serialHandler;

    public void OnClick()
    {
        serialHandler.Write("t");
    }
}
