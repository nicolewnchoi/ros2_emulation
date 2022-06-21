using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Unity.Robotics.ROSTCPConnector;
using RosPos = RosMessageTypes.ApInterfaces.PosMsg;

public class posmessage : MonoBehaviour
{
    // Start is called before the first frame update
    public List<Transform> objects;

    void Start()
    {
        ROSConnection.GetOrCreateInstance().Subscribe<RosPos>("pos_true", posChange);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void posChange(RosPos rosPos)
    {
        var x = rosPos.x[0];
        var y = rosPos.y[0];
        var pos = Camera.main.ScreenToWorldPoint(new Vector3(x, y,Camera.main.nearClipPlane));//convert to normal coordinate
        pos.z = 0;
        objects[0].position = pos;
        //Debug.Log(pos.x + " and " + pos.y);
        //Debug.Log(rosPos.x[0]);
    }
}
