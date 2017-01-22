using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StartButton : MonoBehaviour
{
    public Text enemyCount;

    public SerialHandler serialHandler;

    public void OnClick()
    {
        // 構造体を作成する
        var enemy1s = FindObjectsOfType<Enemy1>();

        var enemies = new List<Enemy>();

        foreach(var enemy1 in enemy1s)
        {
            enemies.Add(new Enemy(0, 0, 1, (int)enemy1.transform.position.x, (int)enemy1.transform.position.x, 1));
            Destroy(enemy1.gameObject);
            enemyCount.text = "0 / 5";
        }

        byte[] testByte = { 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        serialHandler.Write(testByte);
    }
}