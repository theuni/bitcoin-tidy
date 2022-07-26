// Copyright (c) 2022 Cory Fields
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "desig_init.h"

/*
    If a designated initializer is used, ensure that each member has a
    specified or defaulted initial value.
*/

namespace bitcoin {

void DesigInitCheck::registerMatchers(clang::ast_matchers::MatchFinder *finder)
{
    using namespace clang::ast_matchers;

    // For some reason drilling down from initListExpr does not work. Instead
    // match against implicitValueInitExpr and check their ancestors.

    finder->addMatcher(
      implicitValueInitExpr(
        hasAncestor(
          initListExpr(has(designatedInitExpr())).bind("initlist"))
      ).bind("implicitval")
    , this);
}

void DesigInitCheck::check(const clang::ast_matchers::MatchFinder::MatchResult &Result)
{
    if (const auto* member = Result.Nodes.getNodeAs<clang::ImplicitValueInitExpr>("implicitval")) {
        if (const auto* init = Result.Nodes.getNodeAs<clang::InitListExpr>("initlist")) {
            std::string membertype = member->getType().getAsString();
            diag(init->getBeginLoc(), "Designated initializer with uninitialized member of type: " + membertype);
        }
    }
}

} // namespace bitcoin
