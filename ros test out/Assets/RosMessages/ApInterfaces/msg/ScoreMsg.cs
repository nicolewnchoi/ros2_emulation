//Do not edit! This file was generated by Unity-ROS MessageGeneration.
using System;
using System.Linq;
using System.Collections.Generic;
using System.Text;
using Unity.Robotics.ROSTCPConnector.MessageGeneration;

namespace RosMessageTypes.ApInterfaces
{
    [Serializable]
    public class ScoreMsg : Message
    {
        public const string k_RosMessageName = "ap_interfaces/Score";
        public override string RosMessageName => k_RosMessageName;

        public short[] player_score;
        public short[] game_score;

        public ScoreMsg()
        {
            this.player_score = new short[18];
            this.game_score = new short[18];
        }

        public ScoreMsg(short[] player_score, short[] game_score)
        {
            this.player_score = player_score;
            this.game_score = game_score;
        }

        public static ScoreMsg Deserialize(MessageDeserializer deserializer) => new ScoreMsg(deserializer);

        private ScoreMsg(MessageDeserializer deserializer)
        {
            deserializer.Read(out this.player_score, sizeof(short), 18);
            deserializer.Read(out this.game_score, sizeof(short), 18);
        }

        public override void SerializeTo(MessageSerializer serializer)
        {
            serializer.Write(this.player_score);
            serializer.Write(this.game_score);
        }

        public override string ToString()
        {
            return "ScoreMsg: " +
            "\nplayer_score: " + System.String.Join(", ", player_score.ToList()) +
            "\ngame_score: " + System.String.Join(", ", game_score.ToList());
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
