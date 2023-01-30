#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>

double ByVaccaSeries(int numTerms)
{
    // this method is simple but converges slowly
    // calculate gamma by:
    // 1 * (1/2 - 1/3) +
    // 2 * (1/4 - 1/5 + 1/6 - 1/7) +
    // 3 * (1/8 - 1/9 + 1/10 - 1/11 + 1/12 - 1/13 + 1/14 - 1/15) +
    // 4 * ( . . . ) +
    // . . .
    double gamma = 0;
    size_t next = 4;
    
    for(double numerator = 1; numerator < numTerms; ++numerator)
    {
        double delta = 0;
        for(size_t denominator = next/2; denominator < next; denominator+=2)
        {
            // calculate terms two at a time
            delta += 1.0/denominator - 1.0/(denominator + 1);
        }

        gamma += numerator * delta;
        next *= 2;
    }
    return gamma;
}

// based on the C entry
double ByEulersMethod()
{
    //Bernoulli numbers with even indices
    const std::array<double, 8> B2 {1.0, 1.0/6, -1.0/30, 1.0/42, -1.0/30,
        5.0/66, -691.0/2730, 7.0/6};
    
    const int n = 10;

    //n-th harmonic number
    const double h = [] // immediately invoked lambda
    {
        double sum = 1;
        for (int k = 2; k <= n; k++) { sum += 1.0 / k; }
        return sum - log(n);
    }();

    //expansion C = -digamma(1)
    double a = -1.0 / (2*n);
    double r = 1;
    for (int k = 1; k < ssize(B2); k++)
    {
        r *= n * n;
        a += B2[k] / (2*k * r);
    }

    return h + a;
}


void ec_main()
{
    std::cout << std::setprecision(16) << "Vacca series:  " << ByVaccaSeries(32);
    std::cout << std::setprecision(16) << "\nEulers method: " << ByEulersMethod();
}    

//ByEulersMethod();
    
    // std::cout << "\n eT " << eightT(1);
    // std::cout << "\n t3 " << nTerms<3>(1);
    // std::cout << "\n eT " << eightT(2) + eightT(3);
    // std::cout << "\n t4 " << nTerms<4>(1);
    // std::cout << "\n et " << eightT(4) + eightT(5) + eightT(6) + eightT(7);
    // std::cout << "\n t5 " << nTerms<5>(1);
    // 
    // std::cout << "\n";
    // 
    // by2();
  //  by8p();
    //byRange();
//    byRecursion();
//}


#include <algorithm>
#include <execution>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <ranges>


//0.5772149198434514 // Rust
//0.5772149198434515 // Raku
//0.57721566105982735628288082808
//0.57721566490153286 // C
//0.577215663882899 // C++ vacca 34
//0.57721566490153286060651209008240243104215933593992 // correct
//                                    0.57721566105982735628288082808
/*
30 6.9849193144828076555044634312e-09 0.57721565046603307003181271284
30  1.301042606982605320808943361e-16 0.57721565046603307003181271284
31 3.6088749778849227726890170362e-09 0.57721565745095237964790158003
31 6.7220534694101274908462073654e-18 0.57721565046603318105411517536

by8
3 0.10245587745587744765707327588 0.314285714285714279370154145
3 0.10245587745587744765707327588 0.314285714285714279370154145
4 0.06542259265729402639699685551 0.41674159174159175478280303651
4 0.06542259265729402639699685551 0.41674159174159175478280303651
5 0.039977469691389738715159296589 0.48216418439888575342422427639
5 0.039977469691389738715159296589 0.48216418439888575342422427639
6 0.023712116315073378941535864328 0.52214165409027546438380795735
6 0.023712116315073378941535864328 0.52214165409027546438380795735
7 0.013751980587067523520428125039 0.54585377040534888148926029316
7 0.018347840906375194325317323774 0.54585377040534888148926029316
8 0.007835387965322012510105409433 0.55960575099241638419300670648
8 0.012543944762668138293015829277 0.56420161131172408275347152085
9 0.0044009685362881422604486303385 0.56744113895773840017255906787
9 0.0078269110293545038348206333012 0.57674555607439226267985077357
10 0.0024431943882774510845568016748 0.57184210749402653028994336637
10 0.004599944114067992806393903038 0.58457246710374677345356531077
11 0.001343265175746115097296651264 0.57428530188230397790505321609
12 0.00073255598544574407164631235645 0.57562856705805010015808420576
13 0.00039676483720507064838212141211 0.57636112304349584878337964255
14 0.00021363282576200974560189094209 0.57675788788070092572013436438
15 0.00011444353731348770434900902204 0.57697152070646295918265877845
16 6.1035854741933075803123065484e-05 0.57708596424377645028869210364
17 3.2425112294733098245239077961e-05 0.57714700009851838125030099036
18 1.7166186808024772822997908173e-05 0.57717942521081311291197835089
19 9.0599189661590480589486301666e-06 0.57719659139762113930771647574
20 4.7683749926360496115655684957e-06 0.57720565131658729818298070313
21 2.5033959758500385848741052325e-06 0.57721041969157993456462918402
22 1.3113024195373797605107882291e-06 0.57721292308755578481793691026
23 6.8545347620165021855877848095e-07 0.57721423438997532251448774332
24 3.5762788463949257122459816048e-07 0.57721491984345152381763455196
25 1.8626451908668475245519442676e-07 0.57721527747133616337293915421
26 9.6857548842450983082942345299e-08 0.57721546373585530531613585481
27 5.0291419310276785853410858517e-08 0.57721556059340417554892610497
28 2.6077032162089213551182083155e-08 0.57721561088482353785167333626
29 1.3504177350830144376107029114e-08 0.57721563696185573810737423628
30 6.9849193144828076555044634312e-09 0.57721565046603307003181271284
31 3.6088749778849227726890170362e-09 0.57721565745095237964790158003
32 1.8626451495459242474530414538e-09 0.57721566105982735628288082808

by8p
11 0.0026054189659843966092589440109 0.58917241121781471768770188646
12 0.0014426571095278450940213588183 0.59177783018379914725670687403
13 0.0007874019357563908499964000498 0.59322048729332699235072823285
14 0.00042560958261649711742435897577 0.59400788922908343003825848427
15 0.00022844263702346580269253450979 0.59443349881169993409457674716
16 0.0001219530794323575584314767184 0.59466194144872341897922751741
17 6.4818698404895888631749301112e-05 0.59478389452815583204881022539
18 3.4324026452467459868955756974e-05 0.59484871322656074354995325848
19 1.8117634945212512942447347086e-05 0.59488303725301316937645879079
20 9.5361702171642415137853276974e-06 0.59490115488795836107271952642
21 5.0066397580365851194272863722e-06 0.59491069105817551143644550393
22 2.6225649782385396235895314021e-06 0.59491569769793350985764845973
23 1.3708965341894391309907064169e-06 0.59491832026291180390842328052
24 7.1525305145314632682129740715e-07 0.59491969115944598467393689134
25 3.7252833040568589240137953311e-07 0.59492040641249743782026371264
26 1.9371491366548809764935867861e-07 0.59492077894082784350615611402
27 1.0058279159563809912469878327e-07 0.59492097265574150899425376338
28 5.2154051743968921073246747255e-08 0.59492107323853304912120165682
29 2.7008351041746259113551786868e-08 0.59492112539258479309012273006
30 1.3969837682481500706899169018e-08 0.59492115240093579320301842017
31 7.2177497919406752302506902197e-09 0.59492116637077352425677645442
32 3.7252902429507628312421729788e-09 0.594921173588523366504432488



*/


const int numItr = 33;

double twoToN(size_t low, size_t high)
{
    if (high - low < 3)
    {
        return 1.0 / double(low) - 1.0 / double(low + 1.0);
    }
    auto mid = low / 2 + high / 2;
    return twoToN(low, mid) + twoToN(mid, high);
}

auto constexpr eightT = [](size_t i)
{
//    std::cout << " -" << i << "- ";
    double den = i * 8.0;
    return  1.0/den - 1.0/(den+1) + 1.0/(den+2) - 1.0/(den+3)
        + 1.0/(den+4) - 1.0/(den+5) + 1.0/(den+6) - 1.0/(den+7);
};

template<int T>
double nTerms(size_t i)
{
    if constexpr (T == 3)
    {
        return eightT(i);
    }
    else
    {
        size_t exp = 1;
        for(int i = 4; i < T; i++) exp *=2; 
        auto low = (2 * i);
        auto high = low + 1;
  //      std::cout << " exp:" << exp << " low:" <<low << " high:" << high <<" ";
        return nTerms<T-1>(low) + nTerms<T-1>(high);
    }
}


template<int T>
double nTerms2(size_t i)
{
    if constexpr (T == 3)
    {
        return eightT(i);
    }
    else
    {
        size_t exp = 1;
        for(int i = 4; i < T; i++) exp *=2; 
        return nTerms<T-1>(2 * i) + nTerms<T-1>(3 * i);
    }
}



void by2()
{
    std::cout << "by2\n";
    double gamma = 0;
    size_t numTerms = 2;
    size_t nextNumTerms = 4;

    for(double coeff = 1; coeff < numItr; ++coeff)
    {
        double delta = 0;
        for(size_t den = numTerms; den < nextNumTerms; den+=2)
        {
        // std::cout << std::setprecision(29) //<< numTerms << " "
        //  << "*" << coeff << "/" << den << "\n";

            delta += 1.0/den - 1.0/(den+1);
        }

        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }

}



void byRecursion()
{
    std::cout << "byRecursion\n";
    double gamma = 0;
    size_t numTerms = 2;
    size_t nextNumTerms = 4;

    for(double coeff = 1; coeff < numItr; ++coeff)
    {
        double delta = 0;
        delta += twoToN(numTerms, nextNumTerms);

        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }

}

void byRange()
{
    std::cout << "range\n";



    double gamma = 1/2.0 - 1/3.0;
    gamma+= 2/4.0 - 2/5.0 + 2/6.0 - 2/7.0;
    size_t numTerms = 8;
    size_t nextNumTerms = 16;
//    double denom = 2.0;
    for(double coeff = 3; coeff < numItr; ++coeff)
    {
  
         auto r =std::views::iota(numTerms / 8, nextNumTerms / 8) |
         std::views::transform(eightT);

//         double delta = std::reduce(std::execution::parallel_unsequenced_policy(), r.begin(), r.end(), 0.0); 
         double delta = std::reduce(r.begin(), r.end(), 0.0); 



        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }

}

void by8()
{
    std::cout << "by8\n";

    double gamma = 1/2.0 - 1/3.0;
    gamma+= 2/4.0 - 2/5.0 + 2/6.0 - 2/7.0;
    size_t numTerms = 8;
    size_t nextNumTerms = 16;
//    double denom = 2.0;
    for(double coeff = 3; coeff < 33; ++coeff)
    {
        double delta = 0;
        for(size_t den = numTerms; den < nextNumTerms; den+=8)
        {
        //std::cout << std::setprecision(29) << numTerms << " "
        // << "*" << coeff << "/" << den << "\n";
            delta += eightT(den);

            // delta += 1.0/den - 1.0/(den+1) + 1.0/(den+2) - 1.0/(den+3)
            //    + 1.0/(den+4) - 1.0/(den+5) + 1.0/(den+6) - 1.0/(den+7);

        }

        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }
}

void by8p()
{
    std::cout << "by8p\n";
    const int base = 12;

    double gamma = ByVaccaSeries(base);
    size_t numTerms = 1;
    size_t nextNumTerms = 2;
//    double denom = 2.0;
    constexpr int numP = 1024;
    std::array<size_t, numP>arr;
    for(double coeff = base; coeff < numItr; ++coeff)
    {
        double delta = 0;
  //      size_t numloops = numTerms / numP;
        for(size_t den = numTerms; den < nextNumTerms; den+=numP)
        {
            auto end = std::min(arr.end(), arr.begin() + numTerms);
            std::iota(arr.begin(), end, den);
            delta += std::transform_reduce(std::execution::par_unseq,
                arr.begin(), end, 0.0,
                [](auto a, auto b){return a + b;},
      //         eightT);    
                nTerms<base>);    
//                         [](auto a){return nTerms<base>(a * 2);});
 //           std::cout << "den " << den << " il " << end - arr.begin() << "\n";
        }
        // if (!numloops) for(size_t den = numTerms; den < nextNumTerms; den++)
        // {
        // //std::cout << std::setprecision(29) << numTerms << " "
        // // << "*" << coeff << "/" << den << "\n";
        //     delta += eightT(den);
        // }

        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }
}


void by1()
{
    std::cout << "by1\n";

        double gamma = 0;
    size_t numTerms = 2;
    size_t nextNumTerms = 4;
    double denom = 2.0;
    for(double coeff = 1; coeff < 33; ++coeff)
    {
        double delta = 0;
        double sign = 1.0;
        for(size_t den = numTerms; den < nextNumTerms; den++)
        {
//        std::cout << std::setprecision(29) //<< numTerms << " "
 //        << sign << "*" << coeff << "/" << den << "\n";

            delta += sign/denom;

            denom++;
            sign *= -1.0;
        }

        delta *= coeff;
        double newGamma = gamma + delta;
        std::cout  << std::setprecision(29) //<< numTerms << " "
         << coeff << " " << delta << " " << gamma << "\n";
        if (newGamma == gamma) break;
        gamma = newGamma;
        numTerms = nextNumTerms;
        nextNumTerms = numTerms * 2;

    }

}



