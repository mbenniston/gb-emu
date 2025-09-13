import { ForwardedRef, forwardRef, ReactNode } from "react";
import clsx from "clsx";

export const Panel = ({
  children,
  className,
}: {
  children?: ReactNode;
  className?: string;
}) => {
  return (
    <div className={clsx("rounded bg-base-200 shadow", className)}>
      {children}
    </div>
  );
};

export const PanelHeader = function PanelHeader({
  children,
}: {
  children?: ReactNode;
}) {
  return (
    <h3 className="text-sm">
      {children}
      <div className="divider h-[8px] p-0 m-0" />
    </h3>
  );
};

export const PanelContent = forwardRef(function PanelContent(
  { children }: { children?: ReactNode },
  ref: ForwardedRef<HTMLDivElement>,
) {
  return (
    <div
      ref={ref}
      className="w-full h-full flex flex-col items-stretch gap-2 py-1 px-3"
    >
      {children}
    </div>
  );
});

export const PanelBody = forwardRef(function PanelBody(
  { children, className }: { children?: ReactNode; className?: string },
  ref: ForwardedRef<HTMLDivElement>,
) {
  return (
    <div
      ref={ref}
      className={clsx("flex-grow min-h-0 overflow-auto", className)}
    >
      {children}
    </div>
  );
});
