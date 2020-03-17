#include "Tests/AutomationCommon.h"
#include "Math/Matrix.h"

#include "Util/Core/LogUtilLib.h"

DEFINE_SPEC(MyMatrixTest, "My.Math.Matrix", EAutomationTestFlags::EngineFilter | EAutomationTestFlags::ApplicationContextMask);

void MyMatrixTest::Define()
{
	Describe("Initialization", [this]()
	{
		Describe("Constructor with X, Y, Z, W, vectors", [this]()
		{
			It("should init by rows and ONE is at [3][3]", [this]()
			{
				const FVector TEST_X_VEC_ROW { 1, 2, 3 };
				const FVector TEST_YY_VEC_ROW { 4, 5, 6 };
				const FVector TEST_ZZZ_VEC_ROW { 7, 8, 9 };
				const FVector TEST_WWWW_VEC_ROW { 0, -1, -2 };

				const FMatrix Mat { TEST_X_VEC_ROW, TEST_YY_VEC_ROW, TEST_ZZZ_VEC_ROW, TEST_WWWW_VEC_ROW };
				
				const FVector TEST_X_COLUMN_NO_W { TEST_X_VEC_ROW[0], TEST_YY_VEC_ROW[0], TEST_ZZZ_VEC_ROW[0] };
				{
					TestEqual("X columns is initialized correctly", Mat.GetColumn(0), TEST_X_COLUMN_NO_W);
					TestEqual("X row.X is initialized correctly", Mat.M[0][0], TEST_X_VEC_ROW[0]);
					TestEqual("X row.Y is initialized correctly", Mat.M[0][1], TEST_X_VEC_ROW[1]);
					TestEqual("X row.Z is initialized correctly", Mat.M[0][2], TEST_X_VEC_ROW[2]);
					TestEqual("X row.W is initialized correctly with ZERO", Mat.M[0][3], 0.0F);
				}

				{
				// Checking WWWW row: 
				// WARNING [3][3] of the matrix is correctly initialized with ONE!!!
					TestEqual("W row.X is initialized correctly", Mat.M[3][0], TEST_WWWW_VEC_ROW[0]);
					TestEqual("W row.Y is initialized correctly", Mat.M[3][1], TEST_WWWW_VEC_ROW[1]);
					TestEqual("W row.Z is initialized correctly", Mat.M[3][2], TEST_WWWW_VEC_ROW[2]);
					// NOTE here: ONE!!!
					TestEqual("W row.W is initialized correctly with ZERO", Mat.M[3][3], 1.0F);
				}
			});
		});

		Describe("Transform", [this]()
		{
			It("should be that the passed-in row vectors is a NEW basis", [this]()
			{
				const FVector NewSys_Origin { 1, 2, 3 };
				// So, X ort of the new system is old Y
				const FVector NewSys_Xort { 0, 1, 0 };
				// So, YY ort of the new system is old Z
				const FVector NewSys_YYort { 0, 0, 1 };
				// So, YY ort of the new system is old X
				const FVector NewSys_ZZZort { 1, 0, 0 };


				const FVector TestPoint_InNewSys { 1, 2, 3 };
				// Test point in the old system
				const FVector TestPoint = NewSys_Origin + FVector{ TestPoint_InNewSys[2], TestPoint_InNewSys[0], TestPoint_InNewSys[1] };

				const FMatrix Mat { NewSys_Xort, NewSys_YYort, NewSys_ZZZort, NewSys_Origin };
				const FVector OrigTestPoint = Mat.TransformPosition(TestPoint_InNewSys);
				TestEqual("After transform", OrigTestPoint, TestPoint);
			});
		});
	});
}
