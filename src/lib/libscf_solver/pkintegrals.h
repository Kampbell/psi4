#ifndef PKINTEGRALS_H
#define PKINTEGRALS_H

#include <cstddef>
#include <boost/shared_ptr.hpp>
//namespace boost {
//template<class T> class shared_ptr;
//}

using namespace boost;

namespace psi{

using namespace psi;

class PSIO;
class Options;
class Matrix;

namespace scf{
/**
 * Handles SCF computations using Raffanetti's PK presort trick
 */
class PKIntegrals
{
public:
    PKIntegrals(size_t memory, shared_ptr<PSIO> psio, Options& opt,
                int nirreps, const int* sopi, const int *so2index, const int *so2symblk);
    ~PKIntegrals();
    void setup(shared_ptr<Matrix> J, const shared_ptr<Matrix> Da, const shared_ptr<Matrix> Db);
    void setup(shared_ptr<Matrix> J, shared_ptr<Matrix> K, const shared_ptr<Matrix> Da, const shared_ptr<Matrix> Db);
    void setup(shared_ptr<Matrix> J, shared_ptr<Matrix> Ka, shared_ptr<Matrix> Kb,
               const shared_ptr<Matrix> Da, const shared_ptr<Matrix> Db);
    void compute_J();
    void compute_J_and_K();
    void finalize();
private:
    void setup_arrays(bool build_k);

    /// Whether the PK matrices have been initialized
    bool pk_initialized_;
    /// Whether the K matrices are equivalent or not
    bool restricted_;
    /// Number of totally symmetric pairs
    size_t pk_pairs_;
    /// Number of elements in the pk and pj matrices
    size_t pk_size_;
    /// The amount of memory available, in words
    size_t memory_;
    /// The PSIO object to use for I/O
    shared_ptr<PSIO> psio_;
    /// The options object
    Options &options_;
    /// The block of exchange-like integrals
    double *p_k_;
    /// The block of Coulomb-like integrals
    double *p_j_;
    /// The alpha density
    shared_ptr<Matrix> Da_;
    /// The beta density
    shared_ptr<Matrix> Db_;
    /// The J matrix
    shared_ptr<Matrix> J_;
    /// The alpha K matrix
    shared_ptr<Matrix> Ka_;
    /// The beta K matrix
    shared_ptr<Matrix> Kb_;
    /// The number of irreps
    int nirreps_;
    /// The number of SOs per irrep
    const int *sopi_;
    /// The absolute SO to relative (within irrep) lookup array
    const int *so2index_;
    /// The absolute SO to symmetry lookup array
    const int *so2symblk_;
    /// The amount of junk to put in the output
    int print_;
};

}} // End namespaces

#endif // PKINTEGRALS_H