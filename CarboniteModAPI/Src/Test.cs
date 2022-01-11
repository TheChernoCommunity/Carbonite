using System;

namespace Test
{
    public class Test
    {
        public int m_TestVar = 10;
        private string m_PrivateVar;

        public Test()
        {
            m_PrivateVar = "Hello, World!";
        }

        public string StringProperty => m_PrivateVar;

        public void LogPrivateField()
        {
            Console.WriteLine(m_PrivateVar);
        }

        public int GetResult() => m_TestVar; // Terrible code btw, don't do this :|
    }
}