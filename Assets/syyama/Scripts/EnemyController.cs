using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour {

    // 敵1
    public GameObject enemy1;

    // 敵の初期の高さ
    public float defaultPosY = -4.5f;
 
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

        // 敵を配置する処理
        if (Input.GetMouseButtonDown(0))
        {
            // マウス位置座標を取得しスクリーン座標からワールド座標に変換する
            Vector3 position = Camera.main.ScreenToWorldPoint(Input.mousePosition);

            // 敵オブジェクトを配置するポジション
            float setPos = (float)Math.Round(position.x);

            // 70～143までの間に配置可能
            if (setPos < 70.0f && setPos < 144.0f)
            {
                return;
            }

            if (position.y < -2.0f)
            {
                // 重複してゲームオブジェクトを配置しないようにする
                Enemy1[] enemy1s = FindObjectsOfType<Enemy1>();

                // 既存のオブジェクトを確認する
                foreach (Enemy1 enemy1 in enemy1s)
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
