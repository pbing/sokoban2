#include <print>

#include "usage.hpp"

void usage(const std::string_view prgm) {
  std::println("Usage\n"
               "    {} <level>\n\n"
               "Tiles\n"
               "    @       man\n"
               "    +       man on goal\n"
               "    $       box\n"
               "    *       box on goal\n"
               "    #       wall\n"
               "    .       goal\n"
               "    <space> floor\n\n"
               "Control\n"
               "    w       up\n"
               "    a       left\n"
               "    s       down\n"
               "    d       right\n"
               "    q       quit game\n",
               prgm);
}
