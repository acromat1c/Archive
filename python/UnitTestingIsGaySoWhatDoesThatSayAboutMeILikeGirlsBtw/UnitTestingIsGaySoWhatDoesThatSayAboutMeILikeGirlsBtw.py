#geneticMishap.py
def findGenes(genome:str)->list[str]:
    i=[genome.upper(),0,0]
    while True:
        i[1]=i[0][i[2]:].find("ATG")+i[2]+3
        if(i[1]==2):break
        j=[-1,-1,-1]
        j[0]=i[0][i[1]:].find("TAG")
        j[1]=i[0][i[1]:].find("TAA")
        j[2]=i[0][i[1]:].find("TGA")
        try:i[2]=min([k for k in j if k>0])+i[1]
        except:break
        i.append(i[0][i[1]:i[2]])
    try:i[3]
    except IndexError:i.append("No genes found")
    return i[3:]





#test_geneticMishap.py
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