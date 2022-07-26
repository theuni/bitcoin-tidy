// Copyright (c) 2022 Cory Fields
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DESIG_INIT_H
#define DESIG_INIT_H

#include <clang-tidy/ClangTidyCheck.h>

namespace bitcoin {

class DesigInitCheck final : public clang::tidy::ClangTidyCheck {

public:
  DesigInitCheck(clang::StringRef Name, clang::tidy::ClangTidyContext *Context)
      : clang::tidy::ClangTidyCheck(Name, Context) {}

  bool isLanguageVersionSupported(const clang::LangOptions &LangOpts) const override {
      return LangOpts.CPlusPlus;
  }
  void registerMatchers(clang::ast_matchers::MatchFinder *Finder) override;
  void check(const clang::ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace bitcoin

#endif // DESIG_INIT_H
