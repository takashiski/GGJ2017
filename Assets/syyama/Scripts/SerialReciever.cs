using UnityEngine;

/// <summary>
/// シリアルで情報を受信するクラス
/// </summary>
public class SerialReciever : MonoBehaviour {

    public SerialHandler serialHandler;

    void Start()
    {
        serialHandler.OnDataReceived += OnDataReceived;
    }

    void OnDataReceived(string message)
    {
        Debug.Log(message);

    }
}
