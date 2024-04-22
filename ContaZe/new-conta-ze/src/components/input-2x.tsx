import { DocumentDuplicateIcon, TrashIcon } from "@heroicons/react/24/solid"

interface props_2x {
    label1: string;
    label2: string;
}

function Input2x(props:props_2x) {
    return (
      <>
        <div className="col-span-5">
          <div className="col-span-3">
            <label htmlFor="first-name" className="block text-sm font-medium leading-6 text-gray-900 pl-2">
              {props.label1}
            </label>
            <div className="mt-2">
              <input
                placeholder={props.label1}
                type="text"
                name="first-name"
                id="first-name"
                autoComplete="given-name"
                className="block w-full h-12 rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600 sm:text-sm sm:leading-6"
              />
            </div>
          </div>
          <div className="col-span-2 relative">
            <TrashIcon className="text-gray-500 h-8 absolute bottom-2 right-2" />
          </div>
        </div>

        <div className="col-span-5">
          <div className="col-span-3">
            <label htmlFor="first-name" className="block text-sm font-medium leading-6 text-gray-900 pl-2">
              {props.label2}
            </label>
            <div className="mt-2">
              <input
                placeholder={props.label2}
                type="text"
                name="first-name"
                id="first-name"
                autoComplete="given-name"
                className="block w-full h-12 rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600 sm:text-sm sm:leading-6"
              />
            </div>
          </div>
          <div className="col-span-2 relative">
            <TrashIcon className="text-gray-500 h-8 absolute bottom-2 right-2" />
          </div>

        </div>
        <div className="col-span-2 relative">
          <DocumentDuplicateIcon className="text-gray-500 h-8 absolute bottom-2 right-2" />
        </div>
      </>
    )
}

export default Input2x