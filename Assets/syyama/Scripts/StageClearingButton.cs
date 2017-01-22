using UnityEngine;

public class StageClearingButton : MonoBehaviour {

    public GameObject stageController;

    public void OnClick()
    {
        var sc = stageController.GetComponent<StageController>();
        sc.ClearStageCount();

    }
}
