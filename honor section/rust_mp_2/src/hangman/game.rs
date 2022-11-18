// use core::unicode::conversions::to_lower;
use std::{collections::HashSet, hash::Hash};

use crate::hangman::error::{HangmanError, HangmanErrorKind};

/// DO NOT CHANGE THIS, you may use this as you see fit
/// The number of guesses allowed before the game ends.
pub const NUM_GUESSES_TOTAL : usize = 6;

/// Struct to handle a Hangman game and store all necessary game state.
/// Feel free to design this struct however you like, as long as you don't
/// modify any of the function signatures in the impl block.
/// TODO: design the Hangman struct.
#[derive(Debug, Default)]
pub struct Hangman {
    word : String,
    need_guessed : std::collections::HashSet<char>,
    correct_guessed : std::collections::HashSet<char>,
    incorrect_guessed : std::collections::HashSet<char>,
    num_guesses_left : usize,
}

/// Hangman impl block.
/// Your task is to finish all the functions in this block. You may add any
/// helper functions as you need. After you have finished all the functionality
/// below, feel free to run the program and play with the command line interface which should be 
/// fully functional assuming that your code passes all tests. See the README for instructions.
/// Note: Make sure not to change the function signatures below!!!
/// TODO: finish all the functions in the impl block.
impl Hangman {
    /// Instantiates a new Hangman game object for the given word.
    /// Returns an Ok(Hangman) if the word was valid.
    /// Returns an Err(HangmanError) if the word was an empty string or contained non-alpha chars.
    pub fn new(word: String) -> Result<Self, HangmanError> {
        if word.len() == 0 {
            return Err(HangmanError { 
                error_type: HangmanErrorKind::InvalidWord, 
                error_msg: "Invalid word".to_string(), 
                user_input: word.to_lowercase(),
            })
        }
        for c in word.chars() {
            if !c.is_alphabetic() {
                return Err(HangmanError { 
                    error_type: HangmanErrorKind::InvalidWord, 
                    error_msg: "Invalid word".to_string(), 
                    user_input: word.to_lowercase(),
                })
            }
        }
        let word_lower = word.to_lowercase();
        let mut need_guessed : HashSet<char> = std::collections::HashSet::new();
        for c in word_lower.chars() { need_guessed.insert(c); }
        return Ok(Hangman {
            word : word_lower,
            need_guessed : need_guessed,
            correct_guessed : std::collections::HashSet::new(),
            incorrect_guessed : std::collections::HashSet::new(),
            num_guesses_left : NUM_GUESSES_TOTAL
        });
    }

    /// Guesses a character in the hangman game and updates the game state
    /// Note: the guess is case INSENSITIVE (e.g., if the word is "abc," both 'A' and 'a' are correct guesses).
    /// Returns Ok(true) if the guess was valid and correct
    /// Returns Ok(false) if the guess was valid, but incorrect
    /// Returns a GameAlreadyOver error if the game was already finished before the guess
    /// Returns an InvalidCharacter error if the character is not alphabetic
    /// Returns an AlreadyGuessedCharacter error if the character was already guessed 
    /// (either correctly or incorrectly) in the game.
    pub fn guess(&mut self, c: char) -> Result<bool, HangmanError> {
        let x = c.to_ascii_lowercase();
        if self.get_game_result().is_some() {
            return Err(HangmanError { 
                error_type: HangmanErrorKind::GameAlreadyOver, 
                error_msg: "Game already over".to_string(), 
                user_input: x.to_string()
            });
        }
        if !x.is_alphabetic() {
            return Err(HangmanError { 
                error_type: HangmanErrorKind::InvalidCharacter, 
                error_msg: "Invalid char".to_string(), 
                user_input: x.to_string()
            });
        }
        if self.correct_guessed.contains(&x) || self.incorrect_guessed.contains(&x) {
            return Err(HangmanError { 
                error_type: HangmanErrorKind::AlreadyGuessedCharacter, 
                error_msg: "Already guessed char".to_string(), 
                user_input: x.to_string()
            });
        }
        if self.need_guessed.contains(&x) {
            self.correct_guessed.insert(x);
            return Ok(true);
        } else { 
            self.num_guesses_left -= 1;
            self.incorrect_guessed.insert(x);
            return Ok(false);
        };
    }

    /// Returns a reference to the game word converted to lowercase.
    pub fn get_word(&self) -> &String {
        &self.word
    }

    /// Returns the number of guesses left before the guesser loses.
    pub fn get_num_guesses_left(&self) -> usize {
        self.num_guesses_left
    }

    /// Returns a reference to a HashSet of all correct guessed characters.
    pub fn get_correct_guesses(&self) -> &std::collections::HashSet<char> {
        &self.correct_guessed
    }

    /// Returns a reference to a HashSet of all incorrectly guessed characters.
    pub fn get_incorrect_guesses(&self) -> &std::collections::HashSet<char> {
        &self.incorrect_guessed
    }

    /// Returns the result of the game.
    /// Returns Some(true) if the user guessed all the characters in the word without exceeding
    /// the allowed number of guesses.
    /// Returns Some(false) if the user made too many incorrect guesses.
    /// Otherwise, the game is in progress, so return None.
    pub fn get_game_result(&self) -> Option<bool> {
        if self.correct_guessed.len() == self.need_guessed.len() 
           && self.num_guesses_left >= 0 as usize {
            return Some(true);
        } else if self.num_guesses_left <= 0 {
            return Some(false);
        } else {
            return None;
        }
    }
}