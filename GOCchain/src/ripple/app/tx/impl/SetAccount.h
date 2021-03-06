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

#ifndef GOC_TX_SETACCOUNT_H_INCLUDED
#define GOC_TX_SETACCOUNT_H_INCLUDED

#include <GOC/app/tx/impl/Transactor.h>
#include <GOC/basics/Log.h>
#include <GOC/core/Config.h>
#include <GOC/protocol/Indexes.h>
#include <GOC/protocol/Quality.h>
#include <GOC/protocol/TxFlags.h>

namespace GOC {

class SetAccount
    : public Transactor
{
    static std::size_t const DOMAIN_BYTES_MAX = 256;

public:
    explicit SetAccount (ApplyContext& ctx)
        : Transactor(ctx)
    {
    }

    static
    bool
    affectsSubsequentTransactionAuth(STTx const& tx);

    static
    NotTEC
    preflight (PreflightContext const& ctx);

    static
    TER
    preclaim(PreclaimContext const& ctx);

    TER doApply () override;
};

} // GOC

#endif
