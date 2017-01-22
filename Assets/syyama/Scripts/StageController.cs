using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// ステージ情報を管理するクラス
/// </summary>
public class StageController : MonoBehaviour {

    public Text stageCountText;
    public int stageCount = 1;

    /// <summary>
    /// ステージ番号を表示する
    /// </summary>
    public void Update()
    {
        stageCountText.text = GetStageCount();
    }

    /// <summary>
    /// ステージ番号をカウントアップする
    /// </summary>
    public void CountUp()
    {
        stageCount++;
    }

    /// <summary>
    /// ステージ番号を初期化する
    /// </summary>
    public void ClearStageCount()
    {
        stageCount = 1;
    }

    /// <summary>
    /// ステージ番号を取得する
    /// </summary>
    /// <returns></returns>
    public string GetStageCount()
    {
        return stageCount.ToString();
    }
}
