// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x124d4d33e19cc5abd4215dcbc4f9ccdb20380f01fbff465403a2da92a96c16f1"))
		(  305, uint256("0x0a8fb3b45ee68dc4f6b5e5779d6e6a949a88484e448f644288b7d6e5e1541b3b"))
		(  1278, uint256("0xed4206eab901354a8eaa7c34855d5d3d87f5ea36214624f5974ac55380452ffd"))
		(  3449, uint256("0x6692bd84ebdd42c57005e5a9d16d555f80b920da1906e6770bf9cd25eeec391f"))
		(  250000, uint256("0xab2fb016dd8320b69093c8e50b2dea10387084fac2c1658818e60742998a480e"))
		(  500000, uint256("0xc04fdf288a8cf551e6548a88785d09f937a8965ac8c6146c151793ed6153671a"))
		(  600000, uint256("0xcea0a99cc7315cfbce238a710076d3bea4bdd4d63379beec5017013fa1c5f8dc"))
		(  750000, uint256("0x77d95b90179641957149213acf18e85dd420613afa13b5b3f9cb454dc8b8d2df"))
		(  850000, uint256("0x09ed8f9b80d4a4706b782fb174597ab40f447f58bafc3d3c0b5c5500d2a22db1"))
		(  1050000, uint256("0x12013f1cedee1e43bd4b6986a403b7a61cc8c949e487a045c5e5cc8be8dae9f6"))
		(  1450000, uint256("0xa020d7a5011c78dde488f840111a3aec1b44ce9a0067df274bf97c6425963eeb"))
		(  1850000, uint256("0xc0889c9f49092003c69b850fd913c5cb6c1e08ed8e97a6769f1d4ffddc6703c2"))
		(  2050000, uint256("0x97eccc49eabd8899e5b8c55b483cf1d6480f77d2a81ab61cbd51b7f1cf64d185"))
		(  2135000, uint256("0xc2213c3abeb457b775a0b4926ee136f8ca952c79072cce8d218ec868f7668330"))
		(  2155001, uint256("0xd3ba198db317ee3fd681f8f7efcd1e80e5c2e745c715c560b3364edb7eeba5f8"))
		(  2195000, uint256("0x06bdcebd211d00cfa4f3fae81b7c44d5ff1029b5a90c318f90d58e0582337d24"))
		(  2235000, uint256("0xfb02a98cace25305bcc44f8ff38c1913c72877d5f18e18d349d04ab92fb15aa5"))
		(  2275000, uint256("0x400b272a7ecf12e554e973e610707f69dcc847b7bbe6e6a50cc44776e8b9575a"))
		(  2295000, uint256("0xfc87eabd031b8c45b202a1c3b4ebba3aa0dac0aa1d338ae19862b7c6d509de46"))
		(  2315000, uint256("0x1cedf6a6c5e2163c54105165f68d1af20431ba2fa3129d6828591518d415539d"))
		(  2335000, uint256("0x92342a6f5240b3ce92bed622e178b453aedaf8ef3e66ba09e55bf0ef46d8ba0a"))
		(  2352000, uint256("0x196b6c0cf6f7e207eba68e05c59160f1b6ce2fc42176d55c9787ed26b523b9e1"))
		(  2360060, uint256("0x843a1549e55fd9a0880918f11158c7dbfc4ed827f9e9c9b978c46119dbf9027f"))
		(  2382502, uint256("0x9dd53ce07a6d6f0ce3056fd322668f4af05f9fdf5cec69a7642b7eab1943b546"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1383887110, // * UNIX timestamp of last checkpoint block
        2179203,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        8000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (   546, uint256("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70"))
        ( 35000, uint256("2af959ab4f12111ce947479bfcef16702485f04afd95210aa90fde7d1e4a64ad"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1369685559,
        37581,
        300
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {

        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {

        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
