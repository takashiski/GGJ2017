using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyController : MonoBehaviour {

    // 敵1
    public GameObject enemy1;

    // 敵の初期の高さ
    public float defaultPosY = -4.5f;

    public float enemyFirstPos = 0.0f;
    public float enemyLastPos = 128.0f;


    public Text enemyCount;
	
	// Update is called once per frame
	void Update () {

        // 敵を配置する処理
        if (Input.GetMouseButtonDown(0))
        {
            // マウス位置座標を取得しスクリーン座標からワールド座標に変換する
            var position = Camera.main.ScreenToWorldPoint(Input.mousePosition);

            // 敵オブジェクトを配置するポジション
            var setPos = (float)Math.Round(position.x);

            // 70～143までの間に配置可能
            if (setPos < enemyFirstPos && setPos < enemyLastPos)
            {
                return;
            }

            if (position.y < -2.0f)
            {
                var enemy1s = FindObjectsOfType<Enemy1>();

                // 5体以上配置しないようにする
                if (enemy1s.Length >= 5)
                {
                    return;
                }

                // 重複してゲームオブジェクトを配置しないようにする
                foreach (var enemy1 in enemy1s)
                {
                    if (setPos == enemy1.gameObject.transform.position.x)
                    {
                        return;
                    }
                }
                // 敵オブジェクトを配置する
                Instantiate(enemy1, new Vector3((float)Math.Round(position.x), defaultPosY, 0f), transform.rotation);
                enemyCount.text = enemy1s.Length+1 + " / 5";
            }
        }
    }
}
