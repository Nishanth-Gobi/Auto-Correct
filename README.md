## Auto-Spelling-Correction Program

The program replaces missplelled words from an input text file with the closest word in the dictionary(english3.txt) using modified trie data structure.
</br>
##### Parameters while choosing the closest word: </br>

-> We check if any prefix of the misspelled word is a word in the dictionary. </br>
-> We check if the given word is a prefix of a word in the dictionary. </br>
-> Upon both checks returning false, we find the word from the dictionary that would come after the misspelled word if the misspelled word was an entry in the dictionary.
