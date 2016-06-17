#include <tprint.h>
int main(int argc, char ** argv)
{
    tprint("asdf\n");
    tprint("asdf_%s_ghjk\n", "whee");
    tprint("asdf_%%_ghjk\n");
    tprint("asdf_%c_ghjk\n", 'y');
    tprint("asdf_%x_ghjk\n", 0xab); // 0000
    tprint("asdf_%1x_ghjk\n", 0xcd);
    tprint("asdf_%2x_ghjk\n", 0xef01);
    tprint("asdf_%4x_ghjk\n", 0x23456789);
    tprint("asdf_%8x_ghjk\n", 0x0123456789abcdef);
    tprint("asdf_%1d_ghjk\n", 23);
    tprint("asdf_%1d_ghjk\n", 223);
    tprint("asdf_%1d_ghjk\n", 2223);
    tprint("asdf_%d_ghjk\n", -4223);

    tprint("\n");
    tprint("a_%1u_g\n", 23);
    tprint("a_%1u_g\n", 223);
    tprint("a_%1u_g\n", 2223);
    tprint("a_%1u_g\n", 22223);
    tprint("a_%1u_g\n", 222223);
    tprint("a_%1u_g\n", 2222223);
    tprint("a_%1u_g\n", 22222223);
    tprint("a_%1u_g\n", 222222223);
    tprint("a_%1u_g\n", 2222222223);
    tprint("a_%1u_g\n", 22222222223);

    tprint("\n");
    tprint("a_%2u_g\n", 23);
    tprint("a_%2u_g\n", 223);
    tprint("a_%2u_g\n", 2223);
    tprint("a_%2u_g\n", 22223);
    tprint("a_%2u_g\n", 222223);
    tprint("a_%2u_g\n", 2222223);
    tprint("a_%2u_g\n", 22222223);
    tprint("a_%2u_g\n", 222222223);
    tprint("a_%2u_g\n", 2222222223);
    tprint("a_%2u_g\n", 22222222223);

    tprint("\n");
    tprint("a_%4u_g\n", 23);
    tprint("a_%4u_g\n", 223);
    tprint("a_%4u_g\n", 2223);
    tprint("a_%4u_g\n", 22223);
    tprint("a_%4u_g\n", 222223);
    tprint("a_%4u_g\n", 2222223);
    tprint("a_%4u_g\n", 22222223);
    tprint("a_%4u_g\n", 222222223);
    tprint("a_%4u_g\n", 2222222223);
    tprint("a_%4u_g\n", 22222222223);

    tprint("\n");
    tprint("a_%8u_g\n", 23);
    tprint("a_%8u_g\n", 223);
    tprint("a_%8u_g\n", 2223);
    tprint("a_%8u_g\n", 22223);
    tprint("a_%8u_g\n", 222223);
    tprint("a_%8u_g\n", 2222223);
    tprint("a_%8u_g\n", 22222223);
    tprint("a_%8u_g\n", 222222223);
    tprint("a_%8u_g\n", 2222222223);
    tprint("a_%8u_g\n", 22222222223);

    tprint("he%1x, %s %s %s %s %s %8doo\n", 0x77, "the", "pride", "lies", "in", "itself", 2);

    return 0;
}
