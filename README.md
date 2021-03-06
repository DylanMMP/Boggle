Welcome to Boggle!
This code was all written by Dylan Marcum-Pollard for his CS 201 project at The University of Alabama.

Watch me play Boggle at: https://youtu.be/ZvJrO6bZ5-o

This game follows the rules of Boggle. The user generates a board of any size (though larger than 2 x 2 is recommended so that words
can be easily found and smaller than 40 x 40 is recommended to ensure no graphical errors). The user then has to find words on the
randomly generated board. The letter after a letter must be adjacent to that letter and you cannot use the same 'block' twice for the
same word. This game allows for a max word size of 45, as the largest word in the English language is 
pneumonoultramicroscopicsilicovolcanoconiosis which contains 45 letters.

In regards to words storage, your dictionary file MUST be named wordList.txt. This program will only recognize words that are entirely
lower-case, in English (or at least do not contain accents such as É or ñ), and do not contain special characters (such as numbers,
punctuation, etc). So your text file MUST contain entirely lowercase words for the program to function as intended. This is because
according to Boggle rules, proper nouns are not scored and only letters exist on the Boggle dice. This program only uses capitalization
to differentiate between proper nouns and other words because it is (virtually) impossible to have a list of every proper noun 
(since there are so many places and names) to check every word in the word list against. Also, all words need to be on their own line
of the text file as this is how the program differentiates between different words.

For questions regarding features, design decisions, and more see the FAQ below.

In order to play Boggle, you must do the following:
1. Get a textfile in which all non-proper nouns are lower case. 
(If you do not have one such textfile, there are instructions below to get one).
2. Ensure that the text file is named wordList.txt (Capitalization is important!)
3. Place wordList.txt in the src folder.
4. Enter the src folder if you haven't already.
5. Type "make boggle" (Again, capitalization matters!) in the command line.
6. Enjoy!

If you do not have a valid text file, here are two ways to get them:

If on a unix system:
  You can find a dictionary of words in the following folder:
    /urs/share/dict/words or /usr/dict/words
  You can then move a COPY (this file is used for spellchecking, so for your grammar's sake, don't move the folder itself!)of this file
  to the src folder for this program. By typing the following command:
    cp [Insert the directory to your /usr/dict/words/ file here] [Insert the directory to your Boggle src folder here]/wordList.txt
  Please ensure that your words file is named wordList.txt upon doing the above. If not, rename it.
  Also ensure that your words file meets the requirements in paragraph two of this readme (that is: all words that are not proper
  nouns are entirely lower-case) and that each word is on its own line in the text file.
  
  If you can't do the above, get the file from: https://drive.google.com/file/d/1AdqLE0U35zaPPmUFSp2qCtZWGCw0mS23/view?usp=sharing

If not on a unix system:
  I have uploaded my text file on dropbox at the following link: 
    https://drive.google.com/file/d/1AdqLE0U35zaPPmUFSp2qCtZWGCw0mS23/view?usp=sharing
  Download it and then go to step 2 of the setup instructions.

Frequently Asked Questions:

What Data Structures did you use?
I used three data structures when making this project:
  1. A 2d array of structs to hold the board. Because there are never empty spaces and the board is always rectangular, we can use
     a 2d array to contain and navigate our graph. The reason they are a struct is so that instead of needing 2 arrays (one to store
     what letter is at that index on the board and one to store whether it has been checked) we can instead have one array that contains
     both of those values. It's also very easy to perform a depth first search on a 2d array (which is what we do)
  2. A linked list to hold found words and scored words. We use these simply because they're easy to create and navigate. Storage and
     retrieval time isn't as big of an issue here because of the (relatively) small number of found and scored words.
  3. A trie to hold the words in the dictionary. Tries are very efficent at word preservation. The longest time to search through a trie
     is the length of the longest word. It takes a while to create, but in my opinion the fast retrieval time makes up for that tradeoff.
 
 Why Depth First Search?
  We used Depth First Search (DFS) because that's the way I find words in Boggle. I scan around the node for words that contain the next
  in a possible word and then recursively do that. The way the program works, if it sees a letter that isn't a child of the current node
  in the trie, it doesn't iterate down that letter. In practice, this would make our BFS and DFS very similar anyways, since the BFS
  wouldn't be able to go down 'walled off' paths. (I like to think of it as a maze, where the right letters are the only viable paths.
  
The computer I was playing against just quit the game!
  Yes. They can do that. This is because- as per the way multiplayer is coded in the game- either player is allowed to quit. Since a
  player can quit if they ever find they have the lead on their turn, I also gave bots that ability. A bot has a 10% chance of quitting
  the game on their turn. This also keeps games on 50 x 50 boards (which could have 100s of words, potentially) from lasting a long time.

Why is there no timer in multiplayer?
  This was a design decision. I had tested the game with friends without the timer and then later implemented it. We found that we had
  more fun without the timer because it allows for long periods of stress as you look for the word. It's less rushed and more stressful
  because the other player could've found a word in that time too! I considered having timed multiplayer be an option, but I didn't want
  to bog the game down in menus. If you want to play timed multiplayer, just use the clock on your computer or set a timer on your phone.
  
