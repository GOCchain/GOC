//------------------------------------------------------------------------------
/*
    This file is part of GOCd: https://github.com/GOC/GOCd
    Copyright (c) 2012, 2013 GOC Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef GOC_APP_PATHS_CREDIT_H_INCLUDED
#define GOC_APP_PATHS_CREDIT_H_INCLUDED

#include <GOC/ledger/View.h>
#include <GOC/protocol/STAmount.h>
#include <GOC/protocol/IOUAmount.h>

namespace GOC {

/** Calculate the maximum amount of IOUs that an account can hold
    @param ledger the ledger to check against.
    @param account the account of interest.
    @param issuer the issuer of the IOU.
    @param currency the IOU to check.
    @return The maximum amount that can be held.
*/
/** @{ */
STAmount creditLimit (
    ReadView const& view,
    AccountID const& account,
    AccountID const& issuer,
    Currency const& currency);

IOUAmount
creditLimit2 (
    ReadView const& v,
    AccountID const& acc,
    AccountID const& iss,
    Currency const& cur);
/** @} */

/** Returns the amount of IOUs issued by issuer that are held by an account
    @param ledger the ledger to check against.
    @param account the account of interest.
    @param issuer the issuer of the IOU.
    @param currency the IOU to check.
*/
/** @{ */
STAmount creditBalance (
    ReadView const& view,
    AccountID const& account,
    AccountID const& issuer,
    Currency const& currency);
/** @} */

} // GOC

#endif
