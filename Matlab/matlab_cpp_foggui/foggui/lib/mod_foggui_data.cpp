#include "mod_foggui.h"
#include "mod_foggui_private.h"

P_mod_foggui_T mod_fogguiModelClass::mod_foggui_P = {

  {
    {
      {
        707.958984375,
        -0.27180356511368858,
        -0.82404405548492932,
        972.0,
        3169.0836658001936,
        971.0,
        1.0e+95,
        0.0,
        972.0,
        30.0,
        1.040545864177977,
        1.0,
        1.0,
        1.0,
        0.0
      },

      {
        114.5,
        1.918,
        0.0,
        0.0,
        0.595,
        193.32,
        193.32,
        0.0,
        0.0,
        0.0,
        1.0,
        1.0,
        0.0349,
        1.0,
        1.0e+98,
        1.0e+98,
        0.925,
        0.538,
        52.8814,
        48.9153
      },

      {
        68.8,
        3.286,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.168,
        2.173,
        1732.0,
        7.5,
        0.25,
        40400.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0161,
        0.0,
        0.0
      },

      {
        0.177,
        4.68,
        0.3084,
        0.14,
        0.214,
        0.001454440985150966,
        0.0,
        1.0,
        0.0,
        1.0e+99,
        0.0
      },

      {
        2.238,
        4.074,
        4.349,
        4.62,
        0.181,
        1310000.0,
        0.09,
        5.42,
        0.45,
        0.74,
        1.115,
        -1.0,
        20.0,
        5.7425,
        0.0451,
        -1.4763,
        31.6193,
        -100.5211,
        0.0646,
        4.7,
        0.07,
        1.865,
        0.0,
        0.0,
        0.0
      },

      {
        { 0.0, 0.033333333333333333, 0.066666666666666666, 0.13333333333333333,
          0.2, 0.26666666666666666, 0.3, 0.33333333333333331,
          0.48666666666666664, 0.53333333333333333, 0.56666666666666665, 0.6,
          0.6333333333333333, 0.7, 0.73333333333333328, 0.8, 0.8666666666666667,
          1.0, 1.0e+50, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

        { 1.01102, 0.95281, 0.885, 0.86155, 0.87529, 0.89838, 0.90498, 0.90553,
          0.897, 0.66417, 0.53881, 0.31064, 0.165, 0.08522, 0.05443, 0.02914,
          0.0088, 0.0, 1.0e+50, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

        { 0.58333333333333337, 0.66666666666666663, 0.75, 0.83333333333333337,
          0.9, 0.9, 0.83333333333333337, 0.725, 0.375, 0.24166666666666667,
          0.225, 0.21666666666666667, 0.19166666666666668, 0.13333333333333333,
          0.0, 0.0, 0.0, 0.0, 1.0e+50, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
      },

      {
        { 0.0, 48.0, 58.0, 73.0, 83.0, 93.0, 103.0, 123.0, 143.0, 193.0, 243.0,
          293.0, 343.0, 393.0, 443.0, 493.0, 543.0, 593.0, 643.0, 693.0, 743.0,
          793.0, 843.0, 893.0, 943.0, 993.0, 1043.0, 1143.0, 1243.0, 1343.0,
          1443.0, 1543.0, 1643.0, 1743.0, 1843.0, 1943.0, 2043.0, 2543.0, 3043.0,
          3543.0, 4043.0, 4543.0, 5043.0, 6043.0, 7043.0, 8043.0, 9043.0, 0.0 },

        { 28.125, 148.0, 154.0, 140.0, 130.0, 131.0, 131.0, 131.0, 131.0, 129.0,
          126.0, 126.0, 128.0, 130.0, 130.0, 130.0, 133.0, 136.0, 134.0, 129.0,
          123.0, 120.0, 125.0, 133.0, 140.0, 141.0, 141.0, 143.0, 156.0, 160.0,
          152.0, 141.0, 128.0, 103.0, 92.0, 102.0, 114.0, 101.0, 89.0, 83.0,
          97.0, 98.0, 81.0, 31.0, 233.0, 221.0, 117.0, 0.0 },

        { 2.8294420000000002, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
      },

      { 0.457821719431, 0.561794999301, 0.164841178878, 1.62862979289,
        9.9041948195, 2.07944993712e-8, 0.622345673507, 6.63143467643,
        -15.1178385645, 12.9231599364, 1.78598784449e-19, 0.0789915956228,
        4.22805321602, 5.41511649561, -3.09132765571, 4.47612334416,
        1.67211144136, -0.564806640667, 0.58831740027, -0.0339025859434,
        1.8623592706, 0.0, 0.0, 0.0, 0.0, 0.457821719431, 0.561794999301,
        0.164841178878, 1.62862979289, 9.9041948195, 2.07944993712e-8,
        0.622345673507, 6.63143467643, -15.1178385645, 12.9231599364,
        2.92850320867e-5, 0.0789915956228, 4.22805321602, 5.41511649561,
        -3.09132765571, 4.47612334416, 1.67211144136, -0.564806640667,
        0.58831740027, -0.0339025859434, 1.8623592706, 0.0, 0.0, 0.0, 0.0,
        0.45793025943, 0.561794999301, 0.164833942606, 1.62976027663,
        10.0316602278, -6.03040481765e-7, 0.625463364832, 6.68540810877,
        -15.2972801832, 13.1013683066, 7.32125793756e-6, 0.0790466657728,
        4.25147551349, 5.47436843981, -3.10997798368, 4.47605453756,
        1.68137449683, -0.573560345549, 0.605018225543, -0.0339025859434,
        1.86234787544, 0.0, 0.0, 0.0, 0.0, 0.45793025943, 0.561794999301,
        0.164822196742, 1.65690658356, 10.2579474551, -1.81951869498e-7,
        0.627533379859, 6.73269978163, -15.4325745466, 13.2291602906,
        2.92850318088e-5, 0.0794138235552, 4.29177619155, 5.58702526163,
        -3.14262735817, 4.47593165444, 1.69731261812, -0.589105119495,
        0.634405102863, -0.0339025859434, 1.86234255293, 0.0, 0.0, 0.0, 0.0,
        0.45793025943, 0.561794999301, 0.164806453875, 1.70988818308,
        10.6080812964, -3.79499613523e-7, 0.629144046207, 6.78268038402,
        -15.5569665659, 13.3401165593, -2.19637733512e-5, 0.0806019620609,
        4.3510045084, 5.7670587051, -3.19136869292, 4.47573957312, 1.72073624623,
        -0.613159092052, 0.679208793713, -0.0339025859434, 1.86233964742, 0.0,
        0.0, 0.0, 0.0, 0.45793025943, 0.561794999301, 0.164787521747,
        1.78902788842, 11.1284081461, -3.63903738996e-8, 0.631311714405,
        6.85059358532, -15.7252775331, 13.4899649793, 5.1248807708e-6,
        0.0827665944361, 4.43253679421, 5.99139835665, -3.25723692896,
        4.47544961505, 1.75298065309, -0.64890604345, 0.744320528014,
        -0.0339942145537, 1.86233808265, 0.0, 0.0, 0.0, 0.0, 0.457604639431,
        0.561794999301, 0.1647666156, 1.89565484019, 11.9079401363,
        -6.08239106608e-7, 0.635697057753, 6.96085784188, -16.0256258365,
        13.7684541552, -2.85529055472e-5, 0.0858874779007, 4.54182472654,
        5.89165551824, -3.32463486907, 4.47500541386, 1.79620186923,
        -0.702461136243, 0.838719904937, -0.0338109573328, 1.86233738899, 0.0,
        0.0, 0.0, 0.0, 0.45793025943, 0.561794999301, 0.164745538953,
        2.03349147357, 13.1372032339, 2.75527116669e-7, 0.645328347242,
        7.15510596035, -16.610611749, 14.3321133467, 1.098188732e-5,
        0.0899969191811, 4.68788825787, 6.85084655237, -3.47171607583,
        4.47428492266, 1.85396710759, -0.786913839642, 0.980530877976,
        -0.0334444428901, 1.86233731451, 0.0, 0.0, 0.0, 0.0, 0.488864159392,
        0.57058392529, 0.16472695272, 2.09838787139, 13.6330242198,
        -1.81951869498e-7, 0.588739977918, 8.61432693219, -20.0312741637,
        17.2981995485, -2.41601511696e-5, 0.0946512646268, 4.88709890613,
        6.91009093541, -3.6071455125, 4.47297515615, 1.93275097977,
        -0.936615007408, 1.21357899933, -0.0326197853942, 1.86233770535, 0.0,
        0.0, 0.0, 0.0, 0.538141319331, 0.690714260501, 0.164714608773,
        2.10332509913, 13.6330241987, -4.67876235853e-8, 0.602638813527,
        8.54036475162, -19.8456128929, 17.1318231196, 1.90352708529e-5,
        0.0996529264016, 5.17377208925, 7.08302040483, -3.80661397236,
        4.46996858993, 2.0461245551, -1.28924583736, 1.69124707526,
        -0.0317951278983, 1.862338459, 0.0, 0.0, 0.0, 0.0, 0.547692839319,
        0.773849999037, 0.202663615721, 2.10827359147, 13.6330242583,
        -4.52280361323e-7, 0.670962751293, 6.74464285648, -9.14738706191, 0.0,
        1.46425158605e-5, 0.0923332491458, 6.17888976675, 6.38528068375,
        -4.43792267693, 4.47786286526, 2.44362872131, -1.10357605919,
        1.51653178542, -0.0306039559597, 1.86233950328, 0.0, 0.0, 0.0, 0.0,
        0.549538019316, 0.814049998987, 0.219001221166, 2.27852505924,
        0.745079072104, 23.3709106905, 0.338214864885, 1.24048445155,
        13.207146088, 0.0, -0.0129805903101, 0.0847533422559, 6.161963127,
        2.68015683213, -4.23335123394, 4.49296347691, 2.43693457001,
        -1.09859742828, 1.337003639, -0.028404869304, 1.85561545763, 0.0, 0.0,
        0.0, 0.0, 0.54693305932, 0.806962336996, 0.293407070074, 2.37663775225,
        0.991088023184, 30.2779529511, 0.347125220853, 1.69625182544,
        13.52034039, 0.0, -0.0133094612163, 0.11346109434, 5.56569930272,
        0.605107089496, -3.72897306542, 4.49977518232, 2.20112401799,
        -0.899856093112, 1.0023392252, -0.0231820384962, 1.59934183068, 0.0, 0.0,
        0.0, 0.0, 0.542482919325, 0.795001229011, 0.354123127792, 2.45305205321,
        1.24650495748, 35.8204504465, 0.359115657826, 2.07801978977,
        13.2788297224, 0.0, -0.0040266918616, 0.112186997758, 4.69036119854,
        1.34858444805, -3.18626234836, 4.50306848589, 1.85494510679,
        -0.686407303244, 0.814164198761, -0.00183257221314, 1.52773608742, 0.0,
        0.0, 0.0, 0.0, 0.537381539332, 0.776544002034, 0.408234147345,
        2.51874402306, 1.52860596909, 40.5307324365, 0.372837725648,
        2.40105778961, 12.8878002683, 0.0, 0.0157407045498, 0.109111796926,
        4.0957595952, 1.95137816733, -2.82271061641, 4.50510615398,
        1.61979193028, -0.566948123406, 0.653601995764, 0.012828005492,
        1.48840402236, 0.0, 0.0, 0.0, 0.0, 0.531194759339, 0.756333854059,
        0.458391915629, 2.57790348581, 1.84267000893, 44.6649301663,
        0.387706083831, 2.67478143567, 12.5144031997, 0.0, 0.0328724481068,
        0.106187826915, 3.66021180248, 1.56593401611, -5.95110432904,
        4.50654595237, 0.498204158735, -0.48842419098, 0.729898625949,
        0.02941278402, 1.46316757653, 0.0, 0.0, 0.0, 0.0, 0.525225059347,
        0.735814367085, 0.505910965472, 2.63258668952, 2.19018430509,
        48.4084653012, 0.403350808605, 2.90887797715, 12.2329675664, 0.0,
        0.0434150595262, 0.103037888814, 3.32285471358, 1.54288565147,
        -6.03506601826, 4.50765260963, 0.390210385602, -0.431864166917,
        0.804189798742, 0.0421491609026, 1.445277915, 0.0, 0.0, 0.0, 0.0,
        0.517410179356, 0.717975818107, 0.551545988163, 2.68396734248,
        2.57124125939, 51.9184537957, 0.419486693024, 3.11380914991,
        12.0663892972, 0.0, 0.047368538808, 0.102947841833, 3.05093602308,
        1.56061420658, -2.17399779774, 4.5085516616, 0.314520128075,
        -0.388693719416, 0.877124296757, 0.0503957358608, 1.43179328657, 0.0,
        0.0, 0.0, 0.0, 0.510137999365, 0.695909636134, 0.595772168184,
        2.73277326581, 2.98559314741, 55.3338609896, 0.435875736734,
        3.30049414945, 12.0043831477, 0.0, 0.0480274520223, 0.102596434823,
        2.82635457742, 1.55376228048, -2.0844026344, 4.50930924584,
        0.260135747856, -0.354384016936, 0.949759269313, 0.0522283080751,
        1.42115036881, 0.0, 0.0, 0.0, 0.0, 0.503734139373, 0.674771471161,
        0.638908476121, 2.77947917373, 3.43322306615, 58.7767913303,
        0.452314211701, 3.47986211698, 12.0139091281, 0.0, 0.0477346017051,
        0.102031418096, 2.63657698212, 1.54920042467, -2.02345030205,
        4.5099630756, 0.220672721078, -0.326305923632, 1.02307908578,
        0.051678536411, 1.41249561396, 0.0, 0.0, 0.0, 0.0, 0.495810719383,
        0.655076888185, 0.681179375717, 2.82440379803, 3.91468898253,
        62.3510980689, 0.468628018285, 3.66242670873, 12.0463042411, 0.0,
        0.0455382243259, 0.101300832985, 2.47350562666, 1.54634506284,
        -1.9854295295, 4.51053615856, 0.192131093258, -0.302804891289,
        1.09787119877, 0.0494794497553, 1.40528823346, 0.0, 0.0, 0.0, 0.0,
        0.488647079392, 0.635794757209, 0.722748680317, 2.86776379561,
        4.4313361547, 66.1403649974, 0.484671107311, 3.85791293706,
        12.0428537693, 0.0, 0.042170445678, 0.100447181829, 2.33147694962,
        1.54481020859, -1.96630070945, 4.51104344296, 0.17186310661,
        -0.282782362752, 1.17475644773, 0.0471887344888, 1.39917296392, 0.0, 0.0,
        0.0, 0.0, 0.4823517594, 0.620121581229, 0.763739457019, 2.90970605123,
        4.98541813197, 70.2060480747, 0.5003250376, 4.07493787495, 11.9395777012,
        0.0, 0.0398276431404, 0.099506151035, 2.20638938116, 1.54432893946,
        -1.96310549653, 4.51149525116, 0.158037560185, -0.26547634631,
        1.25422363559, 0.0443482475581, 1.39390552814, 0.0, 0.0, 0.0, 0.0,
        0.47464541941, 0.605067083247, 0.804246377485, 2.95032822831,
        5.58015037948, 74.586071436, 0.515498875059, 4.32074231116,
        11.6715793553, 0.0, 0.0371041351903, 0.0985069521526, 2.09518643065,
        1.54470760843, -1.97359614611, 4.51189913967, 0.149342429711,
        -0.250339366361, 1.33666030647, 0.0410496175747, 1.38931169366, 0.0, 0.0,
        0.0, 0.0, 0.468024479418, 0.589187681267, 0.844343721933, 2.98969255437,
        6.21970897306, 79.2940052071, 0.53012903255, 4.60097334561,
        11.1770671127, 0.0, 0.033999921828, 0.0974731780705, 1.99553526012,
        1.54580371588, -1.99603905655, 4.51226094332, 0.144809909149,
        -0.236966517978, 1.42237678169, 0.0372012159269, 1.38526339955, 0.0, 0.0,
        0.0, 0.0, 0.460426679427, 0.574030070286, 0.88409075516, 3.02783556683,
        6.90918071351, 84.3188814027, 0.544178809846, 4.9195215093,
        10.4010189228, 0.0, 0.0314521240682, 0.0964237455985, 1.90561902844,
        1.54750699052, -2.02904717528, 4.51258537888, 0.143708476898,
        -0.225050992876, 1.51162420304, 0.0343607289965, 1.38166412536, 0.0, 0.0,
        0.0, 0.0, 0.450875159439, 0.556046399308, 0.92353544723, 3.06477526385,
        7.65447162028, 89.6256412812, 0.557637455484, 5.27841822469,
        9.2983816825, 0.0, 0.0291532490778, 0.0953737639917, 1.82399793146,
        1.54973173249, -2.07150150218, 4.51287640191, 0.145473625696,
        -0.214355479876, 1.60460796131, 0.0311537276226, 1.37843956026, 0.0, 0.0,
        0.0, 0.0, 0.44251757945, 0.541652588326, 0.962717115156, 3.10051647104,
        8.46218313672, 95.1561666605, 0.570518607312, 5.67780057159,
        7.83664910305, 0.0, 0.0265761662867, 0.0943352799352, 1.74951368985,
        1.55240879361, -2.12247392897, 4.51313742302, 0.149661891028,
        -0.204693146141, 1.70149770827, 0.0285881265251, 1.37553143662, 0.0, 0.0,
        0.0, 0.0, 0.435136859459, 0.527835446343, 1.00166834023, 3.13505514883,
        9.33945266699, 100.830913018, 0.582858056267, 6.11594725617,
        5.99769393105, 0.0, 0.0250679871525, 0.0933178945623, 1.68122214734,
        1.55548154726, -2.18118430075, 4.51337144134, 0.155919452019,
        -0.195914621759, 1.80243487948, 0.0262974112583, 1.37289333704, 0.0, 0.0,
        0.0, 0.0, 0.426996359469, 0.515049434359, 1.04041638674, 3.16838184842,
        10.2937678958, 106.55107477, 0.594710791225, 6.58938769697,
        3.77874007768, 0.0, 0.0240137260088, 0.0923292656285, 1.61834467502,
        1.55890350401, -2.24697213839, 4.51358112985, 0.163960143534,
        -0.187898867869, 1.90753840308, 0.0240983246028, 1.37048776827, 0.0, 0.0,
        0.0, 0.0, 0.41820461948, 0.502985213374, 1.07898426882, 3.2130432483,
        11.0974348321, 109.81899091, 0.606375539325, 6.93094460329,
        1.90813998969, 0.0, 0.0233548127973, 0.09137551257, 1.56023251115,
        1.56263517685, -2.31926511224, 4.51376889104, 0.173549717801,
        -0.180546627924, 2.01690907257, 0.0218992379473, 1.36828407187, 0.0, 0.0,
        0.0, 0.0, 0.41006411949, 0.491642783389, 1.11739156647, 3.26533060171,
        11.7364503018, 110.637414318, 0.617805535346, 7.14680775739,
        0.454193270197, 0.0, 0.0230619624797, 0.0904615423238, 1.50634009438,
        1.56664234773, -2.39755980944, 4.51393689561, 0.184494359628,
        -0.173775640195, 2.13063293359, 0.0197001512912, 1.36625690308, 0.0, 0.0,
        0.0, 0.0, 0.400838219501, 0.479475449404, 1.15565505579, 3.31239208881,
        12.4150018097, 111.05806687, 0.628831954418, 7.37955772684,
        -1.17706537714, 0.0, 0.0230619624797, 0.0895913114297, 1.45620479772,
        1.5708957641, -2.48141432387, 4.51408711023, 0.196632160312,
        -0.167517077532, 2.24878393556, 0.0175010646353, 1.36438510571, 0.0, 0.0,
        0.0, 0.0, 0.391937939513, 0.467617454418, 1.19378920399, 3.35408045219,
        13.1339780685, 110.995829193, 0.639511823449, 7.62380572043,
        -2.95444575058, 0.0, 0.0231058900272, 0.0887680376874, 1.40943138778,
        1.57536931499, -2.57043059678, 4.5142213186, 0.209826689349,
        -0.161712858369, 2.37142602299, 0.0153936065895, 1.36265086355, 0.0, 0.0,
        0.0, 0.0, 0.382929119524, 0.455965685433, 1.23180656081, 3.39055153006,
        13.8933706417, 110.376182377, 0.649885472393, 7.87394286581,
        -4.84373143757, 0.0, 0.0230546412222, 0.0879943719179, 1.3656798725,
        1.58004017178, -2.66425214919, 4.5143411392, 0.223962080475,
        -0.156313587932, 2.49861480579, 0.0133777771557, 1.36103905425, 0.0, 0.0,
        0.0, 0.0, 0.375656939533, 0.44214854345, 1.26971807157, 3.42208894766,
        14.6922071724, 109.137191884, 0.65997987388, 8.12454974089,
        -6.80976982163, 0.0, 0.0230912475118, 0.0872725385219, 1.32465596618,
        1.58488768999, -2.76255326293, 4.51444803912, 0.238939227302,
        -0.15127696178, 2.63039889948, 0.0124614910491, 1.35953674884, 0.0, 0.0,
        0.0, 0.0, 0.365671259545, 0.430599887464, 1.30753333004, 3.44902148383,
        15.5285136379, 107.23104117, 0.66981305142, 8.37059539868,
        -8.81783278732, 0.0, 0.0230692837382, 0.0866044515199, 1.28610349911,
        1.58989262591, -2.86503095564, 4.51454334767, 0.254672804381,
        -0.146566513813, 2.76682101134, 0.0120949766062, 1.35813281963, 0.0, 0.0,
        0.0, 0.0, 0.357422219555, 0.418948118479, 1.34526078433, 3.47168789565,
        16.3992889116, 104.625283237, 0.679397911426, 8.60753191174,
        -10.8345659294, 0.0, 0.023083926254, 0.0859918117483, 1.24979826393,
        1.5950383092, -2.97141187131, 4.51462826725, 0.271088910477,
        -0.142150624454, 2.90791883277, 0.0120949766068, 1.35681763391, 0.0, 0.0,
        0.0, 0.0, 0.348304859567, 0.407502575493, 1.38290790562, 3.49042445903,
        17.3005027187, 101.303729141, 0.688745064637, 8.8313356808,
        -12.8286548895, 0.0, 0.0230766049951, 0.0854361893303, 1.21554313054,
        1.60030831966, -3.08143355452, 4.51470388447, 0.288123184974,
        -0.138001726669, 3.05372576432, 0.0120033479956, 1.35558280401, 0.0, 0.0,
        0.0, 0.0, 0.340055819577, 0.395953919508, 1.42048132739, 3.50556271114,
        18.2271098563, 97.2670437924, 0.697864533899, 9.03852290764,
        -14.7713007394, 0.0, 0.0230473199638, 0.0849390951039, 1.18316393128,
        1.60568862508, -3.1948590783, 4.51477117994, 0.305719290782,
        -0.134095665755, 3.20427152678, 0.0120033479961, 1.35442099176, 0.0, 0.0,
        0.0, 0.0, 0.334194659584, 0.384611489522, 1.45798696126, 3.51743077918,
        19.1730855218, 92.5330168804, 0.706766511936, 9.22615259776,
        -16.6365565113, 0.0, 0.0230546412221, 0.0845020439315, 1.1525062219,
        1.61116459169, -3.31145377563, 4.51483103722, 0.323827680506,
        -0.130411177881, 3.35958265915, 0.0119117193853, 1.35332574409, 0.0, 0.0,
        0.0, 0.0 },

      {
        { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4,
          1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8,
          2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0 },

        { 0.022, 0.021863, 0.021725, 0.021588, 0.02145, 0.021487, 0.021523,
          0.02156, 0.02882, 0.032882, 0.033745, 0.026459, 0.023043, 0.021412,
          0.019781, 0.01815, 0.016716, 0.015478, 0.014241, 0.013004, 0.012355,
          0.011706, 0.011057, 0.010408, 0.0097586, 0.0093748, 0.008991,
          0.0086072, 0.0082235, 0.0078397, 0.0076717, 0.0075037, 0.0073358,
          0.0071678, 0.0069998, 0.0068319, 0.0066639, 0.0064959, 0.006328,
          0.00616 },

        { 0.071593, 0.071146, 0.070698, 0.070251, 0.069803, 0.069923, 0.070042,
          0.070161, 0.093461, 0.10642, 0.10915, 0.085455, 0.074336, 0.069074,
          0.063813, 0.058552, 0.053912, 0.049896, 0.045884, 0.041876, 0.039758,
          0.037643, 0.035531, 0.033422, 0.031316, 0.030074, 0.028832, 0.027592,
          0.026352, 0.025114, 0.024567, 0.02402, 0.023474, 0.022929, 0.022384,
          0.021839, 0.021294, 0.02075, 0.020207, 0.019663 },

        { 0.00516, 0.00513, 0.0051, 0.00507, 0.00504, 0.00564, 0.00624, 0.00684,
          0.0134, 0.019228, 0.024324, 0.01532, 0.01476, 0.013937, 0.013114,
          0.012291, 0.01176, 0.01152, 0.01128, 0.01104, 0.010872, 0.010704,
          0.010536, 0.010368, 0.0102, 0.010104, 0.010008, 0.009912, 0.009816,
          0.00972, 0.009696, 0.009672, 0.009648, 0.009624, 0.0096, 0.009576,
          0.009552, 0.009528, 0.009504, 0.00948 },

        { 576.0, 576.0, 576.0, 576.0, 576.0, 576.0, 576.0, 576.0, 574.0, 572.83,
          572.5, 571.67, 571.0, 571.0, 571.0, 571.0, 570.86, 570.57, 570.29,
          570.0, 569.6, 569.2, 568.8, 568.4, 568.0, 567.8, 567.6, 567.4, 567.2,
          567.0, 566.8, 566.6, 566.4, 566.2, 566.0, 565.8, 565.6, 565.4, 565.2,
          565.0 }
      },
      1.971,

      {
        0.0,
        0.0,
        0.0
      },

      {
        0.0
      },

      {
        10.0,
        0.0,
        0.0,
        -9.42477796076938
      }
    },

    {
      { -15.852432542905596, -47.205861327982248, 971.0 },
      0.0,
      30.0,
      1.0,

      { 0.9, 500.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    }
  },

  287.058,

  273.15,

  0.01,

  5.0,

  0.0,

  0.0,

  0.0,

  0.02073,


  { 1.0, -0.9793 },

  0.0,

  0.02073,


  { 1.0, -0.9793 },

  0.0,

  0.12217304763960307,

  -0.12217304763960307,

  0.00082903139469730656,

  -0.00082903139469730656,

  0.0,

  0.0,

  0,

  0,

  0,

  0,

  0,

  1073741824
};