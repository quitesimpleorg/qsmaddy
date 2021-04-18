/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#pragma once

// -----------------------------------------------------------------------------

#include <string>
#include <regex>

#include "maddy/lineparser.h"
#include "maddy/callbackreplacer.h"

// -----------------------------------------------------------------------------

namespace maddy {

// -----------------------------------------------------------------------------

/**
 * LinkParser
 *
 * Has to be used after the `ImageParser`.
 *
 * @class
 */
class LinkParser : public LineParser
{
private:
  std::function<std::string(std::smatch &)> callback = [](std::smatch & match){
    std::string inner = match.str(1);
    std::string link = match.str(2);
    return "<a href=\"" + link + "\">" + inner + "</a>";
  };

  std::regex re = std::regex("\\[([^\\]]*)\\]\\(([^\\]]*)\\)");


public:
  /**
   * Parse
   *
   * From Markdown: `[text](http://example.com)`
   *
   * To HTML: `<a href="http://example.com">text</a>`
   *
   * @method
   * @param {std::string&} line The line to interpret
   * @return {void}
   */
  void
  Parse(std::string& line) override
  {
    line = regex_callback_replacer(re,line,callback);
  }

  void setCallback(std::function<std::string(std::smatch &)> callback)
  {
    this->callback = callback;
  }
}; // class LinkParser

// -----------------------------------------------------------------------------

} // namespace maddy
