using UnityEngine;

/// <summary>
/// シリアライズ通信をテストするためのクラス
/// </summary>
public class SerialTest : MonoBehaviour {

    public SerialHandler serialHandler;

    public void OnClick()
    {
        //byte[] testByte = { 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        byte[] testByte = { 0x0a, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a };
        serialHandler.Write(testByte);
    }
}
