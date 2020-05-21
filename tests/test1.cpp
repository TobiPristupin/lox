#include "gtest/gtest.h"
#include "../Scanner.h"

TEST(tester, test1){
    Scanner scanner("hola");
    EXPECT_EQ(scanner.scanTokens().front().type, TokenType::IDENTIFIER);
}
