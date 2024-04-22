import unittest
from main import parser

class TestParser(unittest.TestCase):
    
    def test_max(self):
        args = parser.parse_args(['1', '2', '3'])
        self.assertEqual(args.accumulate(args.integers), 3)
    
    def test_sum(self):
        args = parser.parse_args(['1', '2', '3', '--sum'])
        self.assertEqual(args.accumulate(args.integers), 6)
    
    def test_power2(self):
        args = parser.parse_args(['1', '2', '3', '--power2'])
        self.assertEqual(args.accumulate(args.integers), [1, 4, 9])
        
if __name__ == '__main__':
    unittest.main()