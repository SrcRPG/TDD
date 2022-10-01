#include "gmock/gmock.h"
#include "Soundex.h"

// Refactoring (reading friendly)
using namespace testing;



class SoundexEncoding: public Test {
	public:
		Soundex soundex;
};

//1.

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
	ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}
TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
	ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

// RULE #2 

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropiateDigits){
	ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));	
}
// Unrecognized characters

TEST_F(SoundexEncoding, IgnoresNonAlphabetics){
	ASSERT_THAT(soundex.encode("A#"), Eq("A000"));	
}

// Multiple characters

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits){
	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));	
}

// Limiting length

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters){
	ASSERT_THAT(soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters){
        ASSERT_THAT(soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings){
	ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));

	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter){
        ASSERT_THAT(soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st){
        ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants){
        ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparateByVowels){
        ASSERT_THAT(soundex.encode("Jbob"), Eq("J110"));
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}


