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

#ifndef GOC_APP_LEDGER_ACCOUNTSTATESF_H_INCLUDED
#define GOC_APP_LEDGER_ACCOUNTSTATESF_H_INCLUDED

#include <GOC/app/ledger/AbstractFetchPackContainer.h>
#include <GOC/nodestore/Database.h>
#include <GOC/shamap/SHAMapSyncFilter.h>

namespace GOC {

// This class is only needed on add functions
// sync filter for account state nodes during ledger sync
class AccountStateSF : public SHAMapSyncFilter
{
public:
    AccountStateSF(NodeStore::Database& db, AbstractFetchPackContainer& fp)
        : db_(db)
        , fp_(fp)
    {}

    void
    gotNode(bool fromFilter, SHAMapHash const& nodeHash,
        std::uint32_t ledgerSeq, Blob&& nodeData,
            SHAMapTreeNode::TNType type) const override;

    boost::optional<Blob>
    getNode(SHAMapHash const& nodeHash) const override;

private:
    NodeStore::Database& db_;
    AbstractFetchPackContainer& fp_;
};

} // GOC

#endif