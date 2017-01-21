using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SerialReciever : MonoBehaviour {

    public SerialHandler serialHandler;

    private List<Vector3> angleCache = new List<Vector3>();
    public int angleCacheNum = 10;

    void Start()
    {
        serialHandler.OnDataReceived += OnDataReceived;
    }

    void OnDataReceived(string message)
    {
        Debug.Log(message);

    }
}
