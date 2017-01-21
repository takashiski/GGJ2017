using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour {

    // 敵1
    public GameObject enemy1;

    // 敵の初期の高さ
    public float defaultPosY = -4.5f;
	
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
            if (setPos < 70.0f && setPos < 144.0f)
            {
                return;
            }

            if (position.y < -2.0f)
            {
                // 重複してゲームオブジェクトを配置しないようにする
                var enemy1s = FindObjectsOfType<Enemy1>();

                // 既存のオブジェクトを確認する
                foreach (var enemy1 in enemy1s)
                {
                    if (setPos == enemy1.gameObject.transform.position.x)
                    {
                        return;
                    }
                }
                // 敵オブジェクトを配置する
                Instantiate(enemy1, new Vector3((float)Math.Round(position.x), defaultPosY, 0f), transform.rotation);
            }
        }
    }
}
