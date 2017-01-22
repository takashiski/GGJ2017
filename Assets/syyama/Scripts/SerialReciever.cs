using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SerialReciever : MonoBehaviour {

    public SerialHandler serialHandler;

    void Start()
    {
        //serialHandler.OnDataReceived += OnDataReceived;
    }

    void OnDataReceived(string message)
    {
        Debug.Log(message);

    }
}
