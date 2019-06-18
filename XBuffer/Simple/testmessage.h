
namespace testsimple {

    struct simplemessage
    {
        bool bool_;
        double number_;
        string string_;
    };

    struct fullmessage
    {
        bool[] boolarr_;
        double[] numberarr_;
        string[] stringarr_;
        simplemessage maparr_;
        simplemessage[] maparr_
    };
}