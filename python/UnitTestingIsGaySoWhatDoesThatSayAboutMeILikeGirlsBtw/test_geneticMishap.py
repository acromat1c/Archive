from geneticMishap import *
import unittest





class Test_genome(unittest.TestCase):

    def test_emty_string(self):
        result = findGenes("")
        self.assertEqual(result[0], "No genes found")

    def test_rubbish_string(self):
        result = findGenes("I AM A STRING WITH NO GENES WHATSOEVER")
        self.assertEqual(result[0], "No genes found")
        
    def test_good_string(self):
        result = findGenes("ATGAACAGCTAG")
        self.assertEqual(result[0], "AACAGC")
      
    def test_gooder_string(self):
        result = findGenes("ATGAACAGCTAGAAGCGTAATGAACACCTAG")
        self.assertEqual(result, ["AACAGC", "AACACC"])





if __name__ == '__main__':
    unittest.main()