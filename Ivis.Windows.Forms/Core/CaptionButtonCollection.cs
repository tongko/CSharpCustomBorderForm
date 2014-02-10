using System.Collections;
using System.Collections.Generic;

namespace Ivis.Windows.Forms
{
	internal class CaptionButtonCollection : IEnumerable<CaptionButton>
	{
		#region IEnumerable<CaptionButton> Implementation

		IEnumerator<CaptionButton> IEnumerable<CaptionButton>.GetEnumerator()
		{
			throw new System.NotImplementedException();
		}

		IEnumerator IEnumerable.GetEnumerator()
		{
			throw new System.NotImplementedException();
		}

		#endregion


		#region CaptionButton Enumerator

		public class Enumerator
		{

		}

		#endregion
	}
}
