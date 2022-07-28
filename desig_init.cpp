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
          initListExpr(has(designatedInitExpr())).bind("rootinitlist")),
        hasParent(initListExpr().bind("initlist"))
      ).bind("implicitval")
    , this);
}

void DesigInitCheck::check(const clang::ast_matchers::MatchFinder::MatchResult &Result)
{
    const auto* member = Result.Nodes.getNodeAs<clang::ImplicitValueInitExpr>("implicitval");
    const auto* init = Result.Nodes.getNodeAs<clang::InitListExpr>("initlist");
    const auto* rootinit = Result.Nodes.getNodeAs<clang::InitListExpr>("rootinitlist");
    if (!member || !init || !rootinit) return;

    std::string membertype = member->getType().getAsString();
    auto roottype = rootinit->getType().getCanonicalType().getAsString();

    if (rootinit->getID(*Result.Context) == init->getID(*Result.Context)) {
        diag(rootinit->getBeginLoc(), "Designated initializer for " + roottype + " has uninitialized member of type " + membertype);
    } else {
        auto nestedtype = init->getType().getCanonicalType().getAsString();
        diag(rootinit->getBeginLoc(), "Designated initializer for " + roottype + " contains nested object of type " +  nestedtype  + " with unitialized member of type " + membertype);
    }
}

} // namespace bitcoin
