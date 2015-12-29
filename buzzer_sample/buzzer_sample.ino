/*
SparkFun Inventor's Kit, sketch 11
This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
(This sketch was originally developed by D. Cuartielles for K3) This code is completely free for any use.
Version 2.0 6/2012 MDG

BUZZER
  The Arduino has a built-in command called tone() which clicks the buzzer at a certain frequency. This sketch knows the 
  frequencies of the common notes, allowing you to create songs. We're never going to let you down!

Hardware connections:
  The buzzer has two pins. One is positive and one is negative.
  The positive pin is marked by a "+" symbol on both the top and bottom of the buzzer.

  Connect the positive pin to Arduino digital pin 9. (Note that this must be a PWM pin.)
  Connect the negative pin to GND.

This sketch uses the buzzer to play songs.
The Arduino's tone() command will play notes of a given frequency.
We'll provide a function that takes in note characters (a-g),
and returns the corresponding frequency from this table:

  note  frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz

http://peabody.sapp.org/class/st2/lab/notehz/

2	3	4	5	6
C 65	C 131	C 262	C 523	C 1047
C#  69	C# 139	C# 278	C# 554	C# 1109
D 73	D 147	D 294	D 587	D 1175
D#  78	D# 156	D# 311	D# 622	D# 1245
E 82	E 165	E 330	E 659	E 1319
F 87	F 175	F 349	F 699	F 1397
F#  93	F# 185	F# 370	F# 740	F# 1475
G 98	G 196	G 392	G 784	G 1568
G# 104	G# 208	G# 415	G# 831	G# 1661
A 110	A 220	A 440	A 880	A 1760
A# 117	A# 233	A# 466	A# 932	A# 1865
B 124	B 247	B 494	B 988	B 1976

*/

const int buzzerPin = 9;

// We'll set up an array with the notes we want to play
// change these values to make different songs!

// Length must equal the total number of notes and spaces 

const int songLength = 18;

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

// erased highest 3 (GAB) as my buzzer does not support higher pitches
char notes[] = "1234567cdefgabCDEF"; // a space represents a rest

// Beats is an array of values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 150;


void setup() 
{
  pinMode(buzzerPin, OUTPUT);
}


void loop() 
{
  int i, duration;

  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

  // We only want to play the song once, so we'll pause forever:
  while(true){}
  // If you'd like your song to play over and over,
  // remove the above statement
}


int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 18;  // number of notes we're storing

  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = {'1','2','3','4','5','6','7','c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F'};
  int frequencies[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 699};

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}

