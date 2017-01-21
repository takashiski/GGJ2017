using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartButton : MonoBehaviour
{
    public GameObject border;
    public GameObject message;

    public SerialHandler serialHandler;

    public void OnClick()
    {
        // オブジェクトを非表示にする
        gameObject.SetActive(false);
        border.SetActive(false);
        message.SetActive(false);

        // 構造体を作成する
        var enemy1s = FindObjectsOfType<Enemy1>();

        var enemies = new List<Enemy>();

        foreach(var enemy1 in enemy1s)
        {
            enemies.Add(new Enemy(0, 0, 1, (int)enemy1.transform.position.x, (int)enemy1.transform.position.x, 1));
        }

        serialHandler.Write("testtesttest");
    }
}