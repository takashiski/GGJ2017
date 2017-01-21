using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour {

    // 敵1
    public GameObject enemy1;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

        // 敵を配置する処理
        if (Input.GetMouseButtonDown(0))
        {
            // Vector3でマウス位置座標を取得する
            Vector3 position = Input.mousePosition;

            // マウス位置座標をスクリーン座標からワールド座標に変換する
            Vector3 screenToWorldPointPosition = Camera.main.ScreenToWorldPoint(position);

            // 敵オブジェクトを配置する
            Instantiate(enemy1, new Vector3((float)Math.Round(screenToWorldPointPosition.x), -4.5f, 0f), transform.rotation);
        }
    }
}
