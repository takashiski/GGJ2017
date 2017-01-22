using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class StartButton : MonoBehaviour
{
    public Text enemyCount;

    public SerialHandler serialHandler;

    public byte length = 64;

    public GameObject stageController;

    public void OnClick()
    {
        // 構造体を作成する
        var enemy1s = FindObjectsOfType<Enemy1>();

        var enemies = new List<Enemy>();

        byte cnt = 1;
        byte[] sendBytes = new byte[3];
        sendBytes[0] = 200;
        sendBytes[1] = 250;
        sendBytes[2] = 0;       // 敵の数

        foreach (var enemy1 in enemy1s)
        {
            enemies.Add(new Enemy(0, (byte)enemy1.transform.position.x, 1, 0, 144));
            Destroy(enemy1.gameObject);
            enemyCount.text = "0 / 5";

            cnt++;
        }

        sendBytes[2] = (byte)((int)cnt - 1);

        foreach (Enemy enemy in enemies)
        {
            sendBytes = Enumerable.Concat(sendBytes, Enemy2Byte(enemy)).ToArray();
        }

        serialHandler.Write(sendBytes);

        // ステージ名をインクリメント
        stageController.GetComponent<StageController>().CountUp();
    }

    byte[] Enemy2Byte (Enemy enemy)
    {
        byte[] temp = new byte[5];

        temp[0] = enemy._type;
        temp[1] = enemy._position;
        temp[2] = enemy._speed;
        temp[3] = enemy._range_first;
        temp[4] = enemy._range_last;

        return temp;
    }
}