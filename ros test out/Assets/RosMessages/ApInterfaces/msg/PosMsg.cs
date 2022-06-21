//Do not edit! This file was generated by Unity-ROS MessageGeneration.
using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using Unity.Robotics.ROSTCPConnector.MessageGeneration;

namespace RosMessageTypes.ApInterfaces
{
    [Serializable]
    public class PosMsg : Message
    {
        public const string k_RosMessageName = "ap_interfaces/Pos";
        public override string RosMessageName => k_RosMessageName;

        public sbyte total;
        public long timestamp;
        public short[] x;
        public short[] y;
        public sbyte[] player_id;
        public string[] tag_id;
        public sbyte[] size;

        public PosMsg()
        {
            this.total = 0;
            this.timestamp = 0;
            this.x = new short[18];
            this.y = new short[18];
            this.player_id = new sbyte[18];
            this.tag_id = new string[18];
            this.size = new sbyte[18];
        }

        public PosMsg(sbyte total, long timestamp, short[] x, short[] y, sbyte[] player_id, string[] tag_id, sbyte[] size)
        {
            this.total = total;
            this.timestamp = timestamp;
            this.x = x;
            this.y = y;
            this.player_id = player_id;
            this.tag_id = tag_id;
            this.size = size;
        }

        public static PosMsg Deserialize(MessageDeserializer deserializer) => new PosMsg(deserializer);

        private PosMsg(MessageDeserializer deserializer)
        {
            deserializer.Read(out this.total);
            deserializer.Read(out this.timestamp);
            deserializer.Read(out this.x, sizeof(short), 18);
            deserializer.Read(out this.y, sizeof(short), 18);
            deserializer.Read(out this.player_id, sizeof(sbyte), 18);
            deserializer.Read(out this.tag_id, 18);
            deserializer.Read(out this.size, sizeof(sbyte), 18);
        }

        public override void SerializeTo(MessageSerializer serializer)
        {
            serializer.Write(this.total);
            serializer.Write(this.timestamp);
            serializer.Write(this.x);
            serializer.Write(this.y);
            serializer.Write(this.player_id);
            serializer.Write(this.tag_id);
            serializer.Write(this.size);
        }

        public override string ToString()
        {
            return "PosMsg: " +
            "\ntotal: " + total.ToString() +
            "\ntimestamp: " + timestamp.ToString() +
            "\nx: " + System.String.Join(", ", x.ToList()) +
            "\ny: " + System.String.Join(", ", y.ToList()) +
            "\nplayer_id: " + System.String.Join(", ", player_id.ToList()) +
            "\ntag_id: " + System.String.Join(", ", tag_id.ToList()) +
            "\nsize: " + System.String.Join(", ", size.ToList());
        }

#if UNITY_EDITOR
        [UnityEditor.InitializeOnLoadMethod]
#else
        [UnityEngine.RuntimeInitializeOnLoadMethod]
#endif
        public static void Register()
        {
            MessageRegistry.Register(k_RosMessageName, Deserialize);
        }
    }
}
