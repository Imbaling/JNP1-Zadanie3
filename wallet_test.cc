/**
 * -----------------------------------------------------
 * TESTY
 * -----------------------------------------------------
 *
 * Postęp testów widoczny tutaj:
 * https://docs.google.com/document/d/1uh2I74WaBDYpbx3NNaveHFQmWTynwFJQiLYYg3K7CJg/edit?usp=sharing
 * Fragmenty zaznaczone na zielono mają swój odpowiednik w testach.
 *
 */

 // TODO przekrecenie sie zmiennych - moze MAX liczba B zalatwi sprawe? - w sensie czy danie MAX_INT w parametrach nie psuje?

#define BOOST_TEST_MODULE walletTest
#include <boost/test/included/unit_test.hpp>
#include <ctime>

#include <chrono>
#include <thread>
#include <string>

#include "wallet.h"

using UnitType = unsigned long;

constexpr UnitType UNITS_IN_B = 100000000;
constexpr UnitType MAX_B = 21000000;

/**
 * ----------------------------
 * Wallet tests
 * ----------------------------
 */

/*
template<typename T>
auto cannotConstruct(T x)
->decltype(Wallet(x).opSize()){
    return 1 - Wallet(x).opSize();
}

template<typename T>
bool cannotConstruct(T x) {
    return true;
}
*/



BOOST_AUTO_TEST_SUITE(WalletSuite);

BOOST_AUTO_TEST_CASE(constructorCompilationTests) {

    BOOST_CHECK((std::is_constructible<Wallet, short>::value));
    BOOST_CHECK((std::is_constructible<Wallet, unsigned short>::value));

    BOOST_CHECK((std::is_constructible<Wallet, int>::value));
    BOOST_CHECK((std::is_constructible<Wallet, unsigned int>::value));

    BOOST_CHECK((std::is_constructible<Wallet, long>::value));
    BOOST_CHECK((std::is_constructible<Wallet, unsigned long>::value));

    BOOST_CHECK((std::is_constructible<Wallet, long long>::value));
    BOOST_CHECK((std::is_constructible<Wallet, unsigned long long>::value));



    BOOST_CHECK((std::is_constructible<Wallet, const char *>::value));

    /* todo think czy constructible czy nie */
    //BOOST_CHECK((std::is_constructible<Wallet, char *>::value));

    BOOST_CHECK((std::is_constructible<Wallet, std::string>::value));





    BOOST_CHECK((!std::is_constructible<Wallet, void>::value));


    BOOST_CHECK((!std::is_constructible<Wallet, std::nullptr_t>::value));


    BOOST_CHECK((!std::is_constructible<Wallet, bool>::value));


    BOOST_CHECK((!std::is_constructible<Wallet, char>::value));
    BOOST_CHECK((!std::is_constructible<Wallet, unsigned char>::value));

    BOOST_CHECK((!std::is_constructible<Wallet, wchar_t>::value));
    /* todo nie przechodzi */
    //BOOST_CHECK((!std::is_constructible<Wallet, unsigned wchar_t>::value));

    BOOST_CHECK((!std::is_constructible<Wallet, char16_t>::value));

    BOOST_CHECK((!std::is_constructible<Wallet, char32_t>::value));


    BOOST_CHECK((!std::is_constructible<Wallet, float>::value));
    BOOST_CHECK((!std::is_constructible<Wallet, double>::value));
    BOOST_CHECK((!std::is_constructible<Wallet, long double>::value));


    //BOOST_CHECK(cannotConstruct(12));
    /*BOOST_CHECK(cannotConstruct('2'));
    BOOST_CHECK(cannotConstruct(false));
    BOOST_CHECK(cannotConstruct(true));
    BOOST_CHECK(cannotConstruct(2.2));
    BOOST_CHECK(cannotConstruct((long double) 2.2));
    BOOST_CHECK(cannotConstruct((double) 2.2));
    BOOST_CHECK(cannotConstruct((float) 2.2));

    bool b = false;
    float f = 0.001;
    double d = 256;
    long double ld = 4224;
    char c = 'f';


    BOOST_CHECK(cannotConstruct(b));
    BOOST_CHECK(cannotConstruct(f));
    BOOST_CHECK(cannotConstruct(d));
    BOOST_CHECK(cannotConstruct(ld));
    BOOST_CHECK(cannotConstruct(c));

    //BOOST_CHECK(std::is_constructible());*/

}

BOOST_AUTO_TEST_CASE(conversionCompilationTests) {
    BOOST_CHECK((std::is_convertible<short, Wallet>::value));
    BOOST_CHECK((std::is_convertible<unsigned short, Wallet>::value));

    BOOST_CHECK((std::is_convertible<int, Wallet>::value));
    BOOST_CHECK((std::is_convertible<unsigned int, Wallet>::value));

    BOOST_CHECK((std::is_convertible<long, Wallet>::value));
    BOOST_CHECK((std::is_convertible<unsigned long, Wallet>::value));

    BOOST_CHECK((std::is_convertible<long long, Wallet>::value));
    BOOST_CHECK((std::is_convertible<unsigned long long, Wallet>::value));


    BOOST_CHECK((!std::is_convertible<void, Wallet>::value));


    BOOST_CHECK((!std::is_convertible<std::nullptr_t, Wallet>::value));


    BOOST_CHECK((!std::is_convertible<bool, Wallet>::value));


    BOOST_CHECK((!std::is_convertible<char *, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<const char *, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<std::string, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<std::string *, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<const std::string, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<char, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<unsigned char, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<wchar_t, Wallet>::value));
    /* todo nie przechodzi */
    //BOOST_CHECK((!std::is_convertible<unsigned wchar_t, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<char16_t, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<char32_t, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<float, Wallet>::value));

    BOOST_CHECK((!std::is_convertible<double, Wallet>::value));
    BOOST_CHECK((!std::is_convertible<long double, Wallet>::value));

}

BOOST_AUTO_TEST_CASE(miscCompilationTests) {
    BOOST_CHECK((std::is_move_assignable<Wallet>::value));
    BOOST_CHECK((!std::is_copy_assignable<Wallet>::value));


    BOOST_CHECK((std::is_move_constructible<Wallet>::value));
    BOOST_CHECK((!std::is_copy_constructible<Wallet>::value));

}

BOOST_AUTO_TEST_CASE(emptyConstructor) {
    Wallet empty;

    BOOST_CHECK_EQUAL(empty.getUnits(), 0);

    BOOST_REQUIRE_EQUAL(empty.opSize(), 1);
    BOOST_CHECK_EQUAL(empty[0].getUnits(), 0);
}

BOOST_AUTO_TEST_CASE(initialAmountConstructor) {
    Wallet wallet(15);

    BOOST_CHECK_EQUAL(wallet.getUnits(), 15 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(wallet.opSize(), 1);
    BOOST_CHECK_EQUAL(wallet[0].getUnits(), 15 * UNITS_IN_B);

    BOOST_CHECK_THROW(Wallet(21000001), std::exception);
}


//todo wartosci po wyjatku + operator-
BOOST_AUTO_TEST_CASE(totalOverflows) {
    BOOST_CHECK_THROW(Wallet(MAX_B + 1), std::exception);
    {
        Wallet w(MAX_B / 2);
        Wallet w2(MAX_B / 2);
        BOOST_CHECK_THROW(Wallet(1), std::exception);
    }
    {
        Wallet w(MAX_B / 2);
        Wallet w2(MAX_B / 3);
        BOOST_CHECK_THROW(w2 * 2, std::exception);
    }
    {
        Wallet w(MAX_B / 2);
        Wallet w2(MAX_B / 4);
        BOOST_CHECK_THROW(3 * w, std::exception);
    }
    {
        BOOST_CHECK_EQUAL((Wallet(MAX_B / 2 - 1)
                           + Wallet(MAX_B / 2 + 1)).getUnits(), MAX_B * UNITS_IN_B);
    }
    {
        Wallet w(MAX_B / 2);
        BOOST_CHECK_THROW(Wallet(MAX_B / 2 + 1) + w, std::exception);
        BOOST_CHECK_THROW(Wallet(MAX_B / 2 + 1) + Wallet(MAX_B / 2 + 1), std::exception);
    }
    {
        BOOST_CHECK_THROW(Wallet(-1), std::exception);
        BOOST_CHECK_THROW(Wallet(MAX_B + 1), std::exception);
    }
    {
        Wallet w(MAX_B / 2), w2(MAX_B / 2);
        BOOST_CHECK_EQUAL(Wallet(std::move(w), std::move(w2)).getUnits(), MAX_B * UNITS_IN_B);
    }
    {
        Wallet w("20999999,99999999");
        w += Wallet("0.00000001");
        BOOST_CHECK_EQUAL(w.getUnits(), MAX_B * UNITS_IN_B);
    }
    {
        Wallet w(MAX_B);
        BOOST_CHECK_THROW(w += Wallet("0.00000001"), std::exception);
    }
    {
        Wallet w(MAX_B);
        BOOST_CHECK_THROW(w -= Wallet("0.00000001"), std::exception);
    }
    {
        Wallet w(MAX_B / 2);
        w = Wallet(MAX_B / 2);
        w += Wallet(MAX_B / 2);
        BOOST_CHECK_EQUAL(w.getUnits(), MAX_B * UNITS_IN_B);
        /* TODO: czy np. porownanie w == 100 powinno tworzyc wallet z 100 B?
         * czy takie obiekty tymczasowe powinny byc liczone do limitu */
    }
    {
        Wallet w(MAX_B * 3 / 4);
        w = Wallet(MAX_B / 4);
        w += Wallet(MAX_B / 2);
        BOOST_CHECK_EQUAL(w.getUnits(), MAX_B * 3 / 4 * UNITS_IN_B);
    }
    {
        Wallet w("2,1");
        w *= 10000000;
        BOOST_CHECK_EQUAL(w.getUnits(), MAX_B * UNITS_IN_B);
    }
    {
        Wallet w("0.00234375");
        w *= 8960000000;
        BOOST_CHECK_EQUAL(w.getUnits(), MAX_B * UNITS_IN_B);
    }
    {
        Wallet w("2,1");
        BOOST_CHECK_THROW(w *= 10000001, std::exception);
        BOOST_CHECK_EQUAL(w.getUnits(), 21 * UNITS_IN_B / 10);
    }
    {
        Wallet w("0.00234375");
        BOOST_CHECK_THROW(w *= 8960000001, std::exception);
        BOOST_CHECK_EQUAL(w.getUnits(), 234375);
    }
    {
        Wallet w("21000000");
        Wallet w2(std::move(w));
        BOOST_CHECK_EQUAL(w2.getUnits(), MAX_B * UNITS_IN_B);
    }

    {
        Wallet w1(1'000'000);
        Wallet w2(1'000'000);

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        WalletOperation op1 = w1[0];
        WalletOperation op2 = w2[0];

        BOOST_CHECK_THROW(w2 *= 42, std::exception);

        BOOST_CHECK_EQUAL(w1.getUnits(), 1'000'000 * UNITS_IN_B);
        BOOST_CHECK_EQUAL(w2.getUnits(), 1'000'000 * UNITS_IN_B);

        BOOST_CHECK_EQUAL(w1.opSize(), 1);
        BOOST_CHECK_EQUAL(w2.opSize(), 1);
        BOOST_CHECK_EQUAL(w1[0], op1);
        BOOST_CHECK_EQUAL(w2[0], op2);


    }

    {
        Wallet w1("0,00000001");
        WalletOperation op = w1[0];

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        BOOST_CHECK_THROW(Wallet(MAX_B) + w1, std::exception);
        BOOST_CHECK_EQUAL(w1.getUnits(), 1);
        BOOST_CHECK_EQUAL(w1.opSize(), 1);

        BOOST_CHECK_EQUAL(w1[0], op);
    }

    {
        Wallet w1(1);
        WalletOperation op = w1[0];

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        BOOST_CHECK_THROW(Wallet(MAX_B / 2) + Wallet(MAX_B / 2) + w1, std::exception);
        BOOST_CHECK_EQUAL(w1.getUnits(), 1 * UNITS_IN_B);
        BOOST_CHECK_EQUAL(w1.opSize(), 1);

        BOOST_CHECK_THROW(Wallet(MAX_B / 2) + Wallet(1) + w1 + Wallet(MAX_B  / 2), std::exception);
        BOOST_CHECK_EQUAL(w1.getUnits(), 1 * UNITS_IN_B);
        BOOST_CHECK_EQUAL(w1.opSize(), 1);

        BOOST_CHECK_EQUAL(w1[0], op);
    }

    {
        Wallet w1(MAX_B / 2);
        WalletOperation op = w1[0];

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        BOOST_CHECK_THROW(Wallet(MAX_B / 2 + 1) - w1, std::exception);
        BOOST_CHECK_EQUAL(w1.getUnits(), (MAX_B / 2) * UNITS_IN_B);
        BOOST_CHECK_EQUAL(w1.opSize(), 1);

        BOOST_CHECK_THROW(Wallet(MAX_B / 2) - Wallet(MAX_B /  2) - w1, std::exception);
        BOOST_CHECK_EQUAL(w1.getUnits(), (MAX_B / 2) * UNITS_IN_B);
        BOOST_CHECK_EQUAL(w1.opSize(), 1);

        BOOST_CHECK_EQUAL(w1[0], op);

    }

}

BOOST_AUTO_TEST_CASE(strConstructor) {
    BOOST_CHECK_EQUAL(Wallet("0.00000001").getUnits(), 1);
    BOOST_CHECK_EQUAL(Wallet("0,00000001").getUnits(), 1);
    BOOST_CHECK_EQUAL(Wallet("1.00000001").getUnits(), UNITS_IN_B + 1);
    BOOST_CHECK_EQUAL(Wallet("1,00000001").getUnits(), UNITS_IN_B + 1);

    BOOST_CHECK_EQUAL(Wallet("3.0"), 3);
    BOOST_CHECK_EQUAL(Wallet("3"), 3);
    BOOST_CHECK_EQUAL(Wallet("0.0"), 0);
    BOOST_CHECK_EQUAL(Wallet("0,0"), 0);
    BOOST_CHECK_EQUAL(Wallet("0"), 0);
    BOOST_CHECK_EQUAL(Wallet("10.0"), 10);
    BOOST_CHECK_EQUAL(Wallet("\n\r\t\f\v 10  \n\r\t\v"), 10);
    BOOST_CHECK_EQUAL(Wallet("21000000.00000000").getUnits(), 21000000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(Wallet("21000000,00000000").getUnits(), 21000000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(Wallet("\n\r\t\v21000000.00000000\n\r\t\v").getUnits(), 21000000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(Wallet("10,0").opSize(), 1);
    BOOST_CHECK_EQUAL(Wallet("          10                          ").opSize(), 1);

    BOOST_CHECK_EQUAL(Wallet("3.3").getUnits(), 3 * UNITS_IN_B + 3 * UNITS_IN_B / 10);
    BOOST_CHECK_EQUAL(Wallet("0.05").getUnits(), 5 * UNITS_IN_B / 100);
    BOOST_CHECK_EQUAL(Wallet("10,4").getUnits(), 10 * UNITS_IN_B + 4 * UNITS_IN_B / 10);
    BOOST_CHECK_EQUAL(Wallet("\n\r\t\v 10,4  \n\r\t\v").getUnits(), 10 * UNITS_IN_B + 4 * UNITS_IN_B / 10);
    BOOST_CHECK_EQUAL(Wallet("0,00000001").getUnits(), 1);
    BOOST_CHECK_EQUAL(Wallet("0.00000001").getUnits(), 1);
    BOOST_CHECK_EQUAL(Wallet("0.00000000").getUnits(), 0);
    BOOST_CHECK_EQUAL(Wallet("0.00000000          ").getUnits(), 0);
    BOOST_CHECK_EQUAL(Wallet("       0.00000000").getUnits(), 0);
    BOOST_CHECK_EQUAL(Wallet("\n\r\t\v       0.00000000        \n\r\t\v").getUnits(), 0);

    BOOST_CHECK_THROW(Wallet("0.000000001"), std::exception);
    BOOST_CHECK_THROW(Wallet("00.1"), std::exception);
    BOOST_CHECK_THROW(Wallet("-1.1"), std::exception);
    BOOST_CHECK_THROW(Wallet("1.1.1"), std::exception);
    BOOST_CHECK_THROW(Wallet("1,1,1"), std::exception);
    BOOST_CHECK_THROW(Wallet("-1,1"), std::exception);
    BOOST_CHECK_THROW(Wallet("-1"), std::exception);
    BOOST_CHECK_THROW(Wallet("21000001"), std::exception);

    BOOST_CHECK_THROW(Wallet("0x1"), std::exception);
    BOOST_CHECK_THROW(Wallet("1 0"), std::exception);
    BOOST_CHECK_THROW(Wallet("42 .24"), std::exception);
    BOOST_CHECK_THROW(Wallet("24. 42"), std::exception);
    BOOST_CHECK_THROW(Wallet("24.4 2"), std::exception);
    BOOST_CHECK_THROW(Wallet("2 4.42"), std::exception);
    BOOST_CHECK_THROW(Wallet("0x1        "), std::exception);
    BOOST_CHECK_THROW(Wallet("       0x1"), std::exception);
    BOOST_CHECK_THROW(Wallet("       0x1         "), std::exception);

    BOOST_CHECK_THROW(Wallet(""), std::exception);
    BOOST_CHECK_THROW(Wallet("abcabc"), std::exception);
    BOOST_CHECK_THROW(Wallet("1234a.534"), std::exception);
}

BOOST_AUTO_TEST_CASE(doubleMovingConstructor) {
    BOOST_CHECK_EQUAL(Wallet(Wallet(1), Wallet(2)).opSize(), 3);
    BOOST_CHECK_EQUAL(Wallet(Wallet(1), Wallet(2)), 3);

    Wallet w3(3);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    Wallet w5(5);
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    w3 += 7;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    w5 -= 2;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    w3 *= 9;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    w3 *= 2;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    w5 += 3;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));

    BOOST_REQUIRE_EQUAL(w3.opSize(), 4);
    BOOST_REQUIRE_EQUAL(w5.opSize(), 3);
    std::vector<WalletOperation> ops;
    int i3 = 0;
    int i5 = 0;
    ops.push_back(w3[i3++]);
    ops.push_back(w5[i5++]);

    ops.push_back(w3[i3++]);
    ops.push_back(w5[i5++]);
    ops.push_back(w3[i3++]);
    ops.push_back(w3[i3++]);
    ops.push_back(w5[i5++]);

    Wallet w(std::move(w3), std::move(w5));

    BOOST_CHECK_EQUAL(w, 186);
    BOOST_REQUIRE_EQUAL(w.opSize(), 8);

    for (unsigned i = 0; i < ops.size(); ++i) {
        BOOST_CHECK_EQUAL(w[i], ops[i]);
    }
    BOOST_CHECK(std::is_sorted(ops.begin(), ops.end()));
    BOOST_CHECK(std::unique(ops.begin(), ops.end()) == ops.end());
}

BOOST_AUTO_TEST_CASE(moveConstructor) {
    Wallet w1 = Wallet(1) + Wallet(100) + Wallet(10);
    BOOST_CHECK_EQUAL(w1.getUnits(), 111 * UNITS_IN_B);

    Wallet w2(std::move(w1));
    BOOST_CHECK_EQUAL(w2.getUnits(), 111 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 4);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), 111 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(fromBinaryConstructor) {
    Wallet empty = Wallet::fromBinary("0");
    BOOST_CHECK_EQUAL(empty.getUnits(), 0);

    Wallet thousand = Wallet::fromBinary("1111101000");
    BOOST_CHECK_EQUAL(thousand.getUnits(), 1000 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(Wallet::fromBinary("1111101000").opSize(), 1);
    BOOST_CHECK_EQUAL(Wallet::fromBinary("1111101000")[0].getUnits(),
                      1000 * UNITS_IN_B);

    Wallet power2_20 = Wallet::fromBinary("100000000000000000000");
    BOOST_CHECK_EQUAL(power2_20.getUnits(), (1ll << 20) * UNITS_IN_B);

    BOOST_CHECK_THROW(Wallet::fromBinary("dupadupa"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("10001a"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("10001 001"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("100120010"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary(""), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("100000000000000000000"
                                         "100000000000000000000"
                                         "100000000000000000000"
                                         "100000000000000000000"
                                         "100000000000000000000"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("-1"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("-001"), std::exception);
    BOOST_CHECK_THROW(Wallet::fromBinary("-1000"), std::exception);
}

BOOST_AUTO_TEST_CASE(staticEmpty) {
    BOOST_CHECK_EQUAL(Empty().getUnits(), 0);
    BOOST_CHECK_LT(Empty(), Wallet(1));
    BOOST_CHECK_EQUAL(Empty(), Wallet(0));
    BOOST_CHECK_GT(Wallet("0.000001"), Empty());
}

BOOST_AUTO_TEST_CASE(operationOutOfBounds) {
    Wallet wallet;

    BOOST_REQUIRE_EQUAL(wallet.opSize(), 1);
    BOOST_CHECK_THROW(wallet[2], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(addWalletsRValue) {
    /* Adding Wallet&& and Wallet&&. */
    Wallet w1 = Wallet(1000) + Wallet(10) + Wallet(100) + Wallet(1);

    BOOST_CHECK_EQUAL(w1.getUnits(), 1111 * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w1.opSize(), 4);

    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 1010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 1110 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 1111 * UNITS_IN_B);

    Wallet w2 = (Wallet(1) + Wallet(3) + Wallet(5))
        + (Wallet(1000) + Wallet(10) + Wallet(100) + Wallet(1));
    BOOST_CHECK_EQUAL(w2.getUnits(), (1 + 3 + 5 + 1111) * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w2.opSize(), 4);

    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 4 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 9 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), (1111 + 9) * UNITS_IN_B);

    Wallet w3 = Wallet("1.5") + Wallet("0.5");
    BOOST_CHECK_EQUAL(w3.getUnits(), 2 * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w3.opSize(), 2);

    BOOST_CHECK_EQUAL(w3[0].getUnits(), 15 * UNITS_IN_B / 10);
    BOOST_CHECK_EQUAL(w3[1].getUnits(), 2 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(addWalletsLValue) {
    /* Adding Wallet&& and Wallet&. */
    Wallet w1 = Wallet(1) + Wallet(10) + Wallet(100);
    BOOST_CHECK_EQUAL(w1.opSize(), 3);

    Wallet w2 = Wallet(1000) + w1;

    BOOST_CHECK_EQUAL(w1.getUnits(), 0 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2.getUnits(), 1111 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 4);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 11 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 0 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 2);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 1111 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(addAssignRValue) {
    /* Testing Wallet += Wallet&&. */
    Wallet w = Wallet(10000) + Wallet(1000000) + Wallet(10);
    BOOST_CHECK_EQUAL(w.opSize(), 3);

    w += Wallet(1) + Wallet(100) + Wallet(1000);

    BOOST_CHECK_EQUAL(w.getUnits(), (1 + 100 + 1000 + 10000 + 1000000 + 10) * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w.opSize(), 4);
    BOOST_CHECK_EQUAL(w[0].getUnits(), 10000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w[1].getUnits(), 1010000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w[2].getUnits(), 1010010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w[3].getUnits(), (1 + 100 + 1000 + 10000 + 1000000 + 10) * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(addAssignLValue) {
    /* Testing Wallet += Wallet&. */
    Wallet w1 = Wallet(1) + Wallet(100) + Wallet(1000);
    Wallet w2 = Wallet(10000) + Wallet(1000000) + Wallet(10);
    BOOST_CHECK_EQUAL(w2.opSize(), 3);

    w2 += w1;

    BOOST_CHECK_EQUAL(w1.getUnits(), 0 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2.getUnits(), (1 + 100 + 1000 + 10000 + 1000000 + 10) * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 4);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 1101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 0 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 4);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 10000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 1010000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 1010010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), (1 + 100 + 1000 + 10000 + 1000000 + 10) * UNITS_IN_B);

    w2 += w2;
    BOOST_REQUIRE_EQUAL(w2.opSize(), 4);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 10000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 1010000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 1010010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), (1 + 100 + 1000 + 10000 + 1000000 + 10) * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(subtractWalletsRValue) {
    /* Testing Wallet&& - Wallet&&. */
    Wallet w1 = Wallet(10) - Wallet(5);

    BOOST_CHECK_EQUAL(w1.getUnits(), 5 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 2);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 10 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 5 * UNITS_IN_B);

    Wallet w2 = Wallet(5) - Wallet(5);
    BOOST_CHECK_EQUAL(w2.getUnits(), 0 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 2);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 5 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 0 * UNITS_IN_B);

    BOOST_CHECK_THROW(Wallet(3) - Wallet(4), std::exception);

    Wallet w3 = Wallet("2.0") - Wallet("0.72") - Wallet("0.28");
    BOOST_CHECK_EQUAL(w3.getUnits(), 1 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w3.opSize(), 3);
    BOOST_CHECK_EQUAL(w3[0].getUnits(), 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w3[1].getUnits(), 128 * UNITS_IN_B / 100);
    BOOST_CHECK_EQUAL(w3[2].getUnits(), 1 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(subtractWalletsLValue) {
    /* Testing Wallet&& - Wallet&. */
    Wallet w1 = Wallet(100) + Wallet(1);
    BOOST_CHECK_EQUAL(w1.opSize(), 2);

    Wallet w2 = (Wallet(1000) + Wallet(10)) - w1;

    BOOST_CHECK_EQUAL(w1.getUnits(), 101 * 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2.getUnits(), (1010 - 101) * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 3);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 101 * 2 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 3);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 1010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), (1010 - 101) * UNITS_IN_B);

    BOOST_CHECK_THROW(Wallet(10) - w2, std::exception);

    BOOST_CHECK_EQUAL(w2.getUnits(), (1010 - 101) * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w2.opSize(), 3);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1000 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 1010 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), (1010 - 101) * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(subtractAssignRValue) {
    /* Testing Wallet -= Wallet&&. */
    Wallet w1 = Wallet(100);

    w1 -= Wallet(5);

    BOOST_CHECK_EQUAL(w1.getUnits(), 95 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 2);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 95 * UNITS_IN_B);

    BOOST_CHECK_THROW(w1 -= Wallet(96), std::exception);

    BOOST_CHECK_EQUAL(w1.getUnits(), 95 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 2);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 95 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(subtractAssignLValue) {
    /* Testing Wallet -= Wallet&. */
    Wallet w1 = Wallet(100);
    Wallet w2 = Wallet(10);

    w1 -= w2;

    BOOST_CHECK_EQUAL(w1.getUnits(), 90 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2.getUnits(), 10 * 2 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 2);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 90 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 2);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 10 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 10 * 2 * UNITS_IN_B);

    Wallet w3 = Wallet(101);
    BOOST_CHECK_THROW(w1 -= w3, std::exception);

    BOOST_CHECK_EQUAL(w1.getUnits(), 90 * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w1.opSize(), 2);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 90 * UNITS_IN_B);

    BOOST_CHECK_EQUAL(w3.getUnits(), 101 * UNITS_IN_B);
    BOOST_REQUIRE_EQUAL(w3.opSize(), 1);
    BOOST_CHECK_EQUAL(w3[0].getUnits(), 101 * UNITS_IN_B);
}


BOOST_AUTO_TEST_CASE(multiply) {
    Wallet w1 = Wallet(100) * 5;
    Wallet w2 = 5 * Wallet(100);

    BOOST_CHECK(w1 == w2);
    BOOST_CHECK_EQUAL(w1.getUnits(), 500 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2.getUnits(), 500 * UNITS_IN_B);

    // TODO - czy na pewno chcemy miec usuwana historie przy mnozeniu?
    // TODO - niespojnosc z *=
    BOOST_REQUIRE_EQUAL(w1.opSize(), 1);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 100 * 5 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 1);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 100 * 5 * UNITS_IN_B);

    /* Testing overflows. */
    /* All of those exceed 21MM and should be forbidden. */
    BOOST_CHECK_GT(92233720368LL * UNITS_IN_B, 0);
    BOOST_CHECK_LT(92233720369LL * UNITS_IN_B, 0);
    BOOST_CHECK_LT((2LL * 92233720368LL + 1LL) * UNITS_IN_B, 0);
    BOOST_CHECK_GT((2LL * 92233720368LL + 2LL) * UNITS_IN_B, 0);
    BOOST_CHECK_GT((2LL * 92233720368LL + 3LL) * UNITS_IN_B, 0);

    BOOST_CHECK_THROW(Wallet(1) * 92233720368LL, std::exception);
    BOOST_CHECK_THROW(Wallet(1) * 92233720369LL, std::exception);
    BOOST_CHECK_THROW(Wallet(1) * (2LL * 92233720368LL + 1LL), std::exception);
    BOOST_CHECK_THROW(Wallet(1) * (2LL * 92233720368LL + 2LL), std::exception);
    BOOST_CHECK_THROW(Wallet(1) * (2LL * 92233720368LL + 3LL), std::exception);

    BOOST_CHECK_THROW(Wallet(1) * -5, std::exception);
    BOOST_CHECK_THROW(-1 * Wallet(1), std::exception);

    Wallet w3 = 0 * Wallet(88484);
    BOOST_CHECK_EQUAL(w3.getUnits(), 0 * UNITS_IN_B);

    Wallet w4 = 20 * Wallet("0,05");
    BOOST_CHECK_EQUAL(w4.getUnits(), UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(multiplyAssign) {
    Wallet w1 = Wallet(1) + Wallet(100) + Wallet(10);

    w1 *= 2;
    w1 *= 3;

    BOOST_CHECK_EQUAL(w1.getUnits(), 111 * 3 * 2 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 5);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 111 * 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[4].getUnits(), 111 * 3 * 2 * UNITS_IN_B);

    BOOST_CHECK_THROW(w1 *= -5, std::exception);

    BOOST_CHECK_EQUAL(w1.getUnits(), 111 * 3 * 2 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 5);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 111 * 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[4].getUnits(), 111 * 3 * 2 * UNITS_IN_B);

    w1 *= 0;
    BOOST_CHECK_EQUAL(w1.getUnits(), 0 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w1.opSize(), 6);
    BOOST_CHECK_EQUAL(w1[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[3].getUnits(), 111 * 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[4].getUnits(), 111 * 3 * 2 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w1[5].getUnits(), 0 * UNITS_IN_B);
}

BOOST_AUTO_TEST_CASE(assignOperator) {
    Wallet w1 = Wallet(1) + Wallet(100) + Wallet(10) + Wallet(1000);
    BOOST_CHECK_EQUAL(w1.opSize(), 4);
    BOOST_CHECK_EQUAL(w1.getUnits(), 1111 * UNITS_IN_B);

    Wallet w2 = std::move(w1);

    BOOST_CHECK_EQUAL(w2.getUnits(), 1111 * UNITS_IN_B);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 5);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), 1111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[4].getUnits(), 1111 * UNITS_IN_B);

    w2 = std::move(w2);

    BOOST_REQUIRE_EQUAL(w2.opSize(), 5);
    BOOST_CHECK_EQUAL(w2[0].getUnits(), 1 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[1].getUnits(), 101 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[2].getUnits(), 111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[3].getUnits(), 1111 * UNITS_IN_B);
    BOOST_CHECK_EQUAL(w2[4].getUnits(), 1111 * UNITS_IN_B);
}

std::string walletToString(const Wallet& w) {
    std::ostringstream os;
    os << w;
    return os.str();
}

BOOST_AUTO_TEST_CASE(print) {
    Wallet w1(1);
    Wallet w2(150);
    Wallet w3(8300);
    Wallet w4(82920);
    Wallet w5(1000000);
    Wallet w6(1000500);

    BOOST_CHECK_EQUAL(walletToString(w1), "Wallet[1 B]");
    BOOST_CHECK_EQUAL(walletToString(w2), "Wallet[150 B]");
    BOOST_CHECK_EQUAL(walletToString(w3), "Wallet[8300 B]");
    BOOST_CHECK_EQUAL(walletToString(w4), "Wallet[82920 B]");
    BOOST_CHECK_EQUAL(walletToString(w5), "Wallet[1000000 B]");
    BOOST_CHECK_EQUAL(walletToString(w6), "Wallet[1000500 B]");

    Wallet w7("23234.2422");
    Wallet w8("912.000304");
    Wallet w9("0.0000503");
    Wallet w10("1000,1000");

    BOOST_CHECK_EQUAL(walletToString(w7), "Wallet[23234,2422 B]");
    BOOST_CHECK_EQUAL(walletToString(w8), "Wallet[912,000304 B]");
    BOOST_CHECK_EQUAL(walletToString(w9), "Wallet[0,0000503 B]");
    BOOST_CHECK_EQUAL(walletToString(w10), "Wallet[1000,1 B]");
}

BOOST_AUTO_TEST_CASE(compare) {
    Wallet w1(0);
    Wallet w2(15);
    Wallet w3(20);
    Wallet w4(20);
    Wallet w5(1000000);
    Wallet w6("1000000,000001");
    Wallet w7("999999,99999999");

    BOOST_CHECK(w1 == w1);
    BOOST_CHECK(w1 == 0);
    BOOST_CHECK(0 == w1);

    BOOST_CHECK(w1 <= w1);
    BOOST_CHECK(w1 <= 0);
    BOOST_CHECK(0 <= w1);

    BOOST_CHECK(w1 < w2);
    BOOST_CHECK(0 < w2);
    BOOST_CHECK(w1 < 15);

    BOOST_CHECK(w5 > w3);
    BOOST_CHECK(w5 > 20);
    BOOST_CHECK(1000000 > w3);

    BOOST_CHECK(w2 < w4);
    BOOST_CHECK(w2 < 20);
    BOOST_CHECK(15 < w4);


    BOOST_CHECK(w3 == w4);
    BOOST_CHECK(w3 == 20);
    BOOST_CHECK(20 == w4);


    BOOST_CHECK(w4 <= w3);
    BOOST_CHECK(w4 <= 20);
    BOOST_CHECK(20 <= w3);


    BOOST_CHECK(w2 >= w1);
    BOOST_CHECK(15 >= w1);
    BOOST_CHECK(w2 >= 0);

    BOOST_CHECK(!(w3 == w5));
    BOOST_CHECK(!(20 == w5));
    BOOST_CHECK(!(w3 == 1000000));
    BOOST_CHECK(!(w3 == w5.getUnits() / UNITS_IN_B));
    BOOST_CHECK(!(w3.getUnits() / UNITS_IN_B == w5));


    BOOST_CHECK(!(w3 < w4));
    BOOST_CHECK(!(w3 < 20));
    BOOST_CHECK(!(20 < w4));


    BOOST_CHECK(!(w5 < w2));
    BOOST_CHECK(w6 > w7);

    BOOST_CHECK(w5 != w6);
    BOOST_CHECK(1000000 != w6);
    BOOST_CHECK(w6 != 1000000);

    BOOST_CHECK(w5 < w6);
    BOOST_CHECK(w5.getUnits() / UNITS_IN_B < w6);
    BOOST_CHECK(1000000 < w6);

    BOOST_CHECK(w7 < w5);
    BOOST_CHECK(w7 < 1000000);
    BOOST_CHECK(w7 < w5.getUnits() / UNITS_IN_B);
}

BOOST_AUTO_TEST_SUITE_END();

/**
 * ----------------------------
 * WalletOperation tests
 * ----------------------------
 */

BOOST_AUTO_TEST_SUITE(WalletOperationSuite);

BOOST_AUTO_TEST_CASE(compare) {
    WalletOperation w1(15), w2(30);

    BOOST_CHECK(w1 == w2);
    BOOST_CHECK(w2 == w1);
    BOOST_CHECK(w2 >= w1);
    BOOST_CHECK(w2 <= w1);

    BOOST_CHECK(!(w1 < w2));
    BOOST_CHECK(!(w2 < w1));
    BOOST_CHECK(!(w2 < w2));
    BOOST_CHECK(!(w1 > w2));

    WalletOperation w3(10);
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    WalletOperation w4(10);

    BOOST_CHECK(w3 < w4);
    BOOST_CHECK(w4 > w3);
    BOOST_CHECK(w3 != w4);
    BOOST_CHECK(!(w3 > w4));
    BOOST_CHECK(!(w3 == w4));
}

auto walletOperationToString(const WalletOperation& op) {
    std::ostringstream os;
    os << op;
    return os.str();
}

std::string formatCurrentDate() {
    auto theTime = time(nullptr);
    auto aTime = localtime(&theTime);

    auto day = aTime->tm_mday;
    auto month = aTime->tm_mon + 1;
    auto year = aTime->tm_year + 1900;

    std::ostringstream os;
    os << std::setw(4) << std::setfill('0') << year << "-";
    os << std::setw(2) << std::setfill('0') << month << "-";
    os << std::setw(2) << std::setfill('0') << day;

    return os.str();
}

BOOST_AUTO_TEST_CASE(print) {
    auto date = formatCurrentDate();

    WalletOperation w1(1);
    WalletOperation w2(UNITS_IN_B);
    WalletOperation w3(UNITS_IN_B * 834);
    WalletOperation w4(UNITS_IN_B * 837 + 15);
    WalletOperation w5(UNITS_IN_B * 837 + 50000);
    WalletOperation w6(50000);
    WalletOperation w7(UNITS_IN_B * 15 + 580000);
    WalletOperation w8(UNITS_IN_B * 1050 + 5080000);

    BOOST_CHECK_EQUAL(walletOperationToString(w1), "Wallet balance is 0,00000001 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w2), "Wallet balance is 1 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w3), "Wallet balance is 834 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w4), "Wallet balance is 837,00000015 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w5), "Wallet balance is 837,0005 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w6), "Wallet balance is 0,0005 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w7), "Wallet balance is 15,0058 B after operation made at day " + date);
    BOOST_CHECK_EQUAL(walletOperationToString(w8), "Wallet balance is 1050,0508 B after operation made at day " + date);
}

BOOST_AUTO_TEST_SUITE_END();
